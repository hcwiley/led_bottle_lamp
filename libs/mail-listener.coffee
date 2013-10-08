## thanks to https://github.com/chirag04/mail-listener2/ for the start here
#
Imap = require("imap")
util = require("util")
EventEmitter = require("events").EventEmitter
MailParser = require("mailparser").MailParser

MailListener = (options) ->
  @markSeen = !!options.markSeen
  @mailbox = options.mailbox or "INBOX"
  @fetchUnreadOnStart = !!options.fetchUnreadOnStart
  @mailParserOptions = options.mailParserOptions or {}
  @imap = new Imap(
    user: options.username
    password: options.password
    host: options.host
    port: options.port
    tls: options.tls
    tlsOptions: options.tlsOptions or {}
  )

  @imap.once "ready", imapReady.bind(@)
  @imap.once "close", imapClose.bind(@)
  @imap.on "error", imapError.bind(@)
  @

imapReady = ->
  self = @
  @imap.openBox @mailbox, false, (err, mailbox) ->
    if err
      self.emit "error", err
    else
      self.emit "server:connected"
      parseUnread.call self  if self.fetchUnreadOnStart
      MailListener::mailInterval = setInterval ->
        parseUnread.call self
      , 1000 * 3
      self.imap.on "mail", imapMail.bind(self)

imapClose = ->
  @emit "server:disconnected"
imapError = (err) ->
  @emit "error", err
imapMail = ->
  parseUnread.call this
parseUnread = ->
  self = this
  @imap.search ["UNSEEN"], (err, results) ->
    if err
      self.emit "error", err
    else if results.length > 0
      f = self.imap.fetch(results,
        bodies: ""
        markSeen: self.markSeen
      )
      f.on "message", (msg, seqno) ->
        parser = new MailParser(self.mailParserOptions)
        parser.on "end", (mail) ->
          self.emit "mail", mail

        msg.on "body", (stream, info) ->
          stream.pipe parser


      f.once "error", (err) ->
        self.emit "error", err
    else
      self.emit "no-mail"

module.exports = MailListener
util.inherits MailListener, EventEmitter
MailListener::start = ->
  @imap.connect()

MailListener::stop = ->
  @imap.end()
