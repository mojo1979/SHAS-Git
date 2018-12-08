var express = require('express');
var bodyParser = require('body-parser');
var randoString = require('randomstring');
var shasMongoAuth = require('mongodb').MongoClient;
var localdb = "mongodb://127.0.0.1:27017/"
var router = express.Router();

/* GET users listing. */
router.get('/', function(req, res, next) {
   if (req.query.loginRequired === "true") {
      res.render('login', { title: 'MySHAS | Login', pagetitle: 'MySHAS | Login', loginMsg: 'You need to login to view this page' });
   } else {
      res.render('login', { title: 'MySHAS | Login', pagetitle: 'MySHAS | Login', loginMsg: '' });
   }
});

router.post('/', function(req, res, next) {
   shasMongoAuth.connect(localdb, function (err,db) {
      if(err) throw err;
      var dbo = db.db("MySHAS-DB");
      var userObject = dbo.collection("UserAccounts").findOne({ "userId" : req.body.user_id}, function (err,userObject) {
         if (err) throw err;
         if (!userObject) {
            res.render('login', {title: 'MySHAS | Login', pagetitle: 'MySHAS | Login', loginMsg: req.body.user_id + ' does not exist!' });
            console.log('Login Attempt: [' + req.body.user_id + '] with password: [' + req.body.user_pass + ']');
	    db.close();
         } else if (!(userObject.passWd == req.body.user_pass)) {
            res.render('login', {title: 'MySHAS | Login', pagetitle: 'MySHAS | Login', loginMsg: 'Wrong Password!' });
            console.log('Password Attempt: ' + req.body.user_pass);
	    db.close();
         } else if (userObject && (userObject.passWd == req.body.user_pass)) {
            var sessId = randoString.generate(12);
            var sessionObject = dbo.collection('MySHASSesh').insertOne({ 'sessId' : sessId, 'userId': req.body.user_id })
            res.redirect('/overview?session='+sessId);
	    db.close();
         } else {
            res.render('login', {title: 'MySHAS | Login', pagetitle: 'MySHAS | Login', loginMsg: 'Error Occured!' });
            console.log('Weird Error: ' + req.body.user_id + req.body.user_pass);
	    db.close();
         } 
      });
      
   });
});

module.exports = router;
