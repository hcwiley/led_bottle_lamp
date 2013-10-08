exports.loggerFormat = "dev"
exports.useErrorHandler = true
exports.enableEmailLogin = true
exports.sessionSecret = "i love lamp"

exports.email_username = process.env.EMAIL_USERNAME
exports.email_password = process.env.EMAIL_PASSWORD
exports.email_host = process.env.EMAIL_HOST || "imap.gmail.com"

exports.imp_url = process.env.IMP_URL
