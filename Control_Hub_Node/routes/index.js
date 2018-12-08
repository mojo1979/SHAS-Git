var express = require('express');
var router = express.Router();
var confFilePath = '/Shares/opidrive/ControlHubInterface-NodeJS/public/jsonobjects/deviceconf.json';
var fs = require('fs');

/* GET home page. */
router.get('/', function(req, res, next) {
  let currentConf = JSON.parse(fs.readFileSync(confFilePath));
  var myshasid = currentConf.MySHASId;
  if (myshasid == "") {
    myshasid = "Not Configured";
  }
  res.render('index', { title: 'SHAS Control Hub', version: '1.1 Alpha', devName: currentConf.DeviceName, devId: currentConf.DeviceId, MySHASConf: myshasid  });
});

module.exports = router;
