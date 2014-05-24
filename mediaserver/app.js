
/**
 * Module dependencies.
 */

var express = require('express');
var routes = require('./routes');
var user = require('./routes/user');
var http = require('http');
var path = require('path');
var MongoStore = require('connect-mongo')(express);
var settings = require('./settings');
var flash = require('connect-flash');
var app = express();

// all environments
app.set('port', process.env.PORT || 3000);
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');
app.use(express.logger('dev'));
app.use(express.json());
app.use(express.urlencoded());
app.use(express.methodOverride());
app.use(flash());
app.use(express.cookieParser());
app.use(express.session({
    secret: settings.cookieSecret,
    store: new MongoStore({
        db: settings.db
    })
}));
app.configure(function () {
    app.use(function (req, res, next) {
        res.locals.user = req.session.user;
  //      console.log(req.session.user);
        var err = req.flash('error');
        if (err.length)
            res.locals.error = err;
        var succ = req.flash('success');
  //      console.log('b4 succ');
  //      console.log(succ);
        if (succ.length)
            res.locals.success = succ;
        next();
    });
});
app.use(app.router);
app.use(express.static(path.join(__dirname, 'public')));

// development only
if ('development' == app.get('env')) {
  app.use(express.errorHandler());
}
routes(app);

http.createServer(app).listen(app.get('port'), function(){
  console.log('Express server listening on port ' + app.get('port'));
});
