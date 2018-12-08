var express = require('express');
var router = express.Router();
var shasMongoDB = require('mongodb').MongoClient;
var localdb = 'mongodb://127.0.0.1:27017/'

/* GET users listing. */
router.get('/', function(req, res, next) {
  shasMongoDB.connect(localdb, function (err,db) {
    if(err) throw err;
    var dbo = db.db("MySHAS-DB");
    var SessionObj = dbo.collection("MySHASSesh").findOne({"sessId" : req.query.session}, function (err, sessinfo) {
      if (err) throw err;
      if (!sessinfo) {
        res.redirect('/login?loginRequired=true');
      } else {
        var ControlHubObj = dbo.collection("ControlHubMySHASAssets").findOne({}, function (err,dbmyshasid) {
          if (err) throw err;
          console.log(dbmyshasid.MySHASId);
          res.render('overview', { title: 'MySHAS | Overview', pagetitle: 'MySHAS | Overview', MySHASId : dbmyshasid.MySHASId});
        });
      }
    });
  });
});

module.exports = router;
