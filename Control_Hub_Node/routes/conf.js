var express = require('express');
var router = express.Router();
var confFilePath = '/Shares/opidrive/ControlHubInterface-NodeJS/public/jsonobjects/deviceconf.json';
var fs = require('fs');
var bodyParser = require('body-parser');
var myshasid = "";

/* GET conf page. */
router.get('/', function(req, res, next) {
  let currentConf = JSON.parse(fs.readFileSync(confFilePath));
  myshasid = currentConf.MySHASId;
  if (myshasid == "") {
    myshasid = "Not Configured";
  }
  res.render('conf', { jsHandler: 'configuration_handler.js', title: 'Configuration', jsonString: "No Changes", devName: currentConf.DeviceName, devId: currentConf.DeviceId, MySHASId: myshasid });
});

/* POST conf page. */
router.post('/', function(req, res, next) {
  var currentConf = JSON.parse(fs.readFileSync(confFilePath));
  currentConf["DeviceName"] = ""+req.body.confDevName;
  currentConf["DeviceId"] = ""+req.body.confDevId;
  currentConf["MySHASId"] = ""+req.body.confMySHAS;
  myshasid = currentConf.MySHASId;
  if (myshasid == "") {
    myshasid = "Not Configured";
  }
  let config = JSON.stringify(currentConf);
  fs.writeFileSync(confFilePath, config); 
  res.render('conf', { jsHandler: 'configuration_handler.js', title: 'Configuration', jsonString: "New Configuration Applied!", devName: currentConf.DeviceName, devId: currentConf.DeviceId, MySHASId: myshasid });
});

module.exports = router;