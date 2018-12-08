var express = require('express');
var SerialPort = require('serialport');
var bodyParser = require('body-parser');
var confFilePath = '/Shares/opidrive/ControlHubInterface-NodeJS/public/jsonobjects/deviceconf.json';
var fs = require('fs');
//var portUSB0 = new SerialPort('/dev/ttyUSB0', { baudRate: 115200 });
//var portUSB1 = new SerialPort('/dev/ttyUSB1', { baudRate: 115200 });
//var portUSB2 = new SerialPort('/dev/ttyUSB2', { baudRate: 115200 });
//var portUSB3 = new SerialPort('/dev/ttyUSB3', { baudRate: 115200 });
var router = express.Router();

/* GET devices page. */
router.get('/', function(req, res, next) {
  //res.send(JSON.stringify(sensorObject));
  /*portUSB1.write('R', function(err) { 
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('Command Read Sent');
  });
  portUSB2.write('R', function(err) { 
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('Command Read Sent');
  });
  portUSB3.write('R', function(err) { 
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('Command Read Sent');
  });*/
  //portUSB0.on('data', function (data) {
  //  devStat = 'Got Data!';
  //  console.log('Data Get: ', data);
  //});
  res.render('device', { jsHandler: 'command_handler.js', title: 'Devices', data: 'Ready for Input!' });
});



/*router.post('/', function(req, res, next) {
  portUSB0.write(req.body.commandFAC, function(err) { 
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('CommandFAC Sent');
  });
  /*portUSB1.write(req.body.commandLAV, function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('CommandLAV Sent');
  });
  portUSB2.write(req.body.commandBEAC, function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('CommandBEAC Sent');
  });
  portUSB3.write(req.body.commandBAAC, function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('CommandBAAC Sent');
  });
  res.render('device', { jsHandler: 'command_handler.js', title: 'Devices', data: 'Previous Commands: ' + req.body.commandFAC + ' ' + req.body.commandLAV + ' ' + req.body.commandBEAC + ' ' + req.body.commandBAAC });
});*/

module.exports = router;
