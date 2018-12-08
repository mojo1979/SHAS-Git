var express = require('express');
var bodyParser = require('body-parser');
var randoString = require('randomstring');
var shasMongoClient = require('mongodb').MongoClient;
var localdb = "mongodb://127.0.0.1:27017/"
var router = express.Router();


router.get('/', function(req, res, next) {
  shasMongoClient.connect(localdb, function(err, db) {
    if (err) throw err;
    var dbo = db.db('MySHAS-DB');
    var controlHubAssets = dbo.collection('ControlHubMySHASAssets').findOne({"MySHASId" : req.query.key}, function(err, assetInfo) {
      if (err) throw err;
      if (!assetInfo) { 
        res.send('{"errMsg" : "Wrong or No Key!"}'+req.query.key);
        db.close();
      } else {
        var controlHubData = dbo.collection('ControlHubData').findOne({"MySHASId" : req.query.key}, function(err, chData) {
          if (err) throw err;
          if (!chData) {
            res.send('{ "errMsg" : "No Database Entry!" }');
            db.close();
          } else {
            res.send(JSON.stringify(chData.ActCommands));
            db.close();
          }
        });
      }
    });
  });
});

router.post('/', function(req, res, next) {
  shasMongoClient.connect(localdb, function (err, db) {
    var dbo = db.db('MySHAS-DB');
    var controlHubAssets = dbo.collection('ControlHubMySHASAssets').findOne({"MySHASId" : req.body.key}, function(err, assetInfo) {
      if (err) throw err;
      if (!assetInfo) {
        db.close();
        res.send('{"errMsg" : "Wrong or No Key!"}'+req.body.key);
      } else {
        var controlHubData = dbo.collection('ControlHubData').findOne({"MySHASId" : req.body.key}, function(err, chData) {
          if (err) throw err;
          console.log(req.body.SensData);
          if (!chData) {
            db.close();
            res.send('{ "errMsg" : "No Database Entry!" }');
          } else {
            dbo.collection('ControlHubData').updateOne({ "MySHASId" : req.body.key}, {$set: { "SensData" : JSON.parse(req.body.SensData) }}, function (err, resdb) {
              console.log('Got Sensor Data');
              res.send('OK!');
              db.close();
            });
          }
        });
      }
    });
  });
});

module.exports = router;
