###
Module dependencies.
###
config = require("./config")
express = require("express")
#lessMiddleware = require('less-middleware')
path = require("path")
http = require("http")
https = require("https")
#socketIo = require("socket.io")
path = require('path')
pubDir = path.join(__dirname, 'public')
MailListener = require "./libs/mail-listener"

# create app, server, and web sockets
app = express()
server = http.createServer(app)
#io = socketIo.listen(server)

# Make socket.io a little quieter
#io.set "log level", 1

app.configure ->
  bootstrapPath = path.join(__dirname, 'assets','css', 'bootstrap')
  app.set "port", process.env.PORT or 3000
  app.set "views", __dirname + "/views"
  app.set "view engine", "jade"
  
  # use the connect assets middleware for Snockets sugar
  app.use require("connect-assets")()
  app.use express.favicon()
  app.use express.logger(config.loggerFormat)
  app.use express.bodyParser()
  app.use express.methodOverride()
  app.use express.cookieParser(config.sessionSecret)
  app.use express.session(secret: "shhhh")
  app.use app.router
  #app.use lessMiddleware
        #src: path.join(__dirname,'assets','css')
        #paths  : bootstrapPath
        #dest: path.join(__dirname,'public','css')
        #prefix: '/css'
        #compress: true
  app.use express.static(pubDir)
  app.use express.errorHandler()  if config.useErrorHandler

console.log "username: #{config.email_username}"

mailListener = new MailListener
  username: config.email_username
  password: config.email_password
  host: config.email_host
  port: 993 # imap port
  tls: true
  tlsOptions:
    rejectUnauthorized: false
  mailbox: "INBOX" # mailbox to monitor
  markSeen: false# all fetched email willbe marked as seen and not fetched next time
  fetchUnreadOnStart: true # use it only if you want to get all unread email on lib start. Default is `false`,
  mailParserOptions: # options to be passed to mailParser lib.
    streamAttachments: true

# start listener. You can stop it calling `stop method`
mailListener.start()

# subscribe to server connected event
mailListener.on "server:connected", ->
  console.log "imap connected"

# subscribe to error events
mailListener.on "error", (err) ->
  console.log "error happened", err

hasMail = "init"

mailListener.on "mail", (mail) ->
  # do something with mail object including attachments
  console.log "mail arrived"
  if config.imp_url && (hasMail=="init" || hasMail == false)
    https.get "#{config.imp_url}?blue=0&red=1", (res) ->
      console.log res.statusCode
      hasMail = true

mailListener.on "no-mail", () ->
  # do something with mail object including attachments
  console.log "no mail"
  if config.imp_url && (hasMail=="init" || hasMail == true)
    https.get "#{config.imp_url}?blue=1&red=0", (res) ->
      console.log res.statusCode
      hasMail = false


## it's possible to access imap object from node-imap library for performing additional actions. E.x.
#mailListener.imap.move :msguids, :mailboxes, ->

# you need to be signed for this business!
app.all "/auth/login", (req, res) ->
  console.log req.body.password
  console.log process.env.STUDIO_PASSWORD
  if req.body.password?.match(process.env.STUDIO_PASSWORD)
    req.session['auth'] = 'so-good'
    return res.redirect('/')
  return res.render('auth/login.jade', info:"you clearly don't know whats up")

# UI routes
app.get "/", (req, res) ->
  res.render "index.jade",
    title: "Lamp"

server.listen app.get("port"), ->
  console.log "Express server listening on port " + app.get("port")

