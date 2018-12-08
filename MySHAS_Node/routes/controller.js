var express = require('express');
var router = express.Router();
var shasMongoDB = require('mongodb').MongoClient;
var localdb = 'mongodb://127.0.0.1:27017/'

/* GET users listing. */
router.get('/', function(req, res, next) {
  shasMongoDB.connect(localdb, function (err,db) {
    if(err) throw err;
    var dbo = db.db("MySHAS-DB");
    var acMenuOptions = 'option value="none"';
    var SessionObj = dbo.collection("MySHASSesh").findOne({"sessId" : req.query.session}, function (err, sessinfo) {
      if (err) throw err;
      if (!sessinfo) {
	db.close();
        res.redirect('/login?loginRequired=true');
      } else {
        if (req.query.update == "sensors") {
          var  ControlHubDataObj =  dbo.collection("ControlHubData").findOne({ "MySHASId" : req.query.key}, function (err,  sensDat) {
            if (err) throw err;
	    if (sensDat == null) {
	      db.close();
	      res.send("!NOSENSDATA");
	    } else {
	      db.close();
              res.send(JSON.stringify(sensDat.SensData));
            }
          });
        } else if (req.query.update == "actuators") {
          dbo.collection('ControlHubData').updateOne({ "MySHASId" : req.query.key}, {$set: {"ActCommands" : { "FACCommand" : req.query.faccomm} }}, function (err, resdb) {
            if (err) throw err;
	    if (req.query.faccom != "") {
            	db.close();
            	console.log("Command Sent to Database!");
            	res.send("Sent!");
	    } else {
		db.close();
		res.send("Empty Command!");
            }
          });
	} else {
          var ControlHubObj = dbo.collection("ControlHubMySHASAssets").findOne({}, function (err,dbmyshasid) {
            if (err) throw err;
            console.log(dbmyshasid.MySHASId);
	    db.close();
            res.render('controller', { title: 'MySHAS | Controller Status', pagetitle: 'Controller Status', MySHASId : dbmyshasid.MySHASId, aclistview : acMenuOptions, listlabel : "None"});
          });
        }
      }
    });
  });
});

module.exports = router;
