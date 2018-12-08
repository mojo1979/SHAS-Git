var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var SerialPort = require('serialport');
var sensorFilePath = '/Shares/opidrive/ControlHubInterface-NodeJS/public/jsonobjects/actsensvalbd.json';
var actComFilePath = '/Shares/opidrive/ControlHubInterface-NodeJS/public/jsonobjects/actcombd.json';
var confFilePath = '/Shares/opidrive/ControlHubInterface-NodeJS/public/jsonobjects/deviceconf.json';
var fs = require('fs');
var https = require('https');
var querystring = require('querystring');

var portUSB0 = new SerialPort('/dev/ttyUSB0', { baudRate: 115200 });
var portUSB1 = new SerialPort('/dev/ttyUSB1', { baudRate: 115200 });
var portUSB2 = new SerialPort('/dev/ttyUSB2', { baudRate: 115200 });
var portUSB3 = new SerialPort('/dev/ttyUSB3', { baudRate: 115200 });
var indexRouter = require('./routes/index');
var devicesRouter = require('./routes/devices');
var confRouter = require('./routes/conf');


var app = express();

// Setup Sensor Get Data Interval & MySHAS Sync
function syncMySHAS() {
	var devConfObj = JSON.parse(fs.readFileSync(confFilePath));
	if (devConfObj.MySHASId != "") {
		console.log("Sync Start");
		var ACDBObj = JSON.parse(fs.readFileSync(sensorFilePath));
		var sensorString = querystring.stringify({
          	'key' : devConfObj.MySHASId,
			'SensData' : JSON.stringify(ACDBObj)
		});
		var optionsGET = {
			hostname: 'myshas.online',
			port: '443',
			path: '/api?key='+devConfObj.MySHASId,
			method: 'GET'
		}
		var reqGetSync = https.request(optionsGET, (res) => {
			console.log('statusCode: ', res.statusCode);
			console.log('headers: ', res.headers);

			res.on('data', (d) => {
				fs.writeFileSync(actComFilePath, d);
				//console.log("Got Commands"+lastCommand+d);
				var commandObj = JSON.parse(d);
				if (commandObj.FACCommand != "!") {
					console.log("Got FAC Commands!");
					portUSB0.write(commandObj.FACCommand, function(err) {
						if (err) throw err;
					});
				}
				if (commandObj.LACCommand != "!") {
					console.log("Got LAC Commands!");
					portUSB1.write(commandObj.LACCommand, function(err) {
						if (err) throw err;
					});
				}
				if (commandObj.BEACCommand != "!") {
					console.log("Got BEAC Commands!")
					portUSB2.write(commandObj.BEACCommand, function(err) {
						if (err) throw err;
					});
				}
				if (commandObj.BACCommand != "!") {
					console.log("Got BAC Commands!");
					portUSB3.write(commandObj.BACCommand, function(err) {
						if (err) throw err;
					});
				}
			});
		});

		reqGetSync.on('error', (e) => {
			console.error(e);
		});
		reqGetSync.end();

		var optionsPOST = {
			hostname: 'myshas.online',
			port: '443',
			path: '/api',
			method: 'POST',
			headers: {
				'Content-Type' : 'application/x-www-form-urlencoded',
				'Content-Length' : Buffer.byteLength(sensorString)
			}
		}

		var reqPostSync = https.request(optionsPOST, (res) => {
			console.log('statusCode: ', res.statusCode);
			console.log('headers: ', res.headers);
			console.log('Posted Data');
		});

		reqPostSync.on('error', (e) => {
			console.error(e);
		});

		reqPostSync.write(sensorString);
		reqPostSync.end();
	}
}

function syncData() {
  portUSB0.write('R', function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    //console.log('ReadSens0 Sent');
    var SensorObj
    var portString = ''+portUSB0.read();
    portString = portString.replace(/[\n\r\0]/g,"");
    //console.log(''+portString);
    setTimeout(function() {
	    sensorObj = JSON.parse(portString);
	    //console.log('parsed');
	    var ACDBObj = JSON.parse(fs.readFileSync(sensorFilePath));
	    //console.log('Read database');
        ACDBObj.ACVals[0].Sensors = sensorObj;
	    //console.log('Added Sensors!');
        var ACDBStr = JSON.stringify(ACDBObj);
        fs.writeFileSync(sensorFilePath, ACDBStr);
	    //console.log('Wrote to Database!');
    }, 10);
  });
portUSB1.write('R', function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    //console.log('ReadSens1 Sent');
    var SensorObj
    var portString = ''+portUSB1.read();
    portString = portString.replace(/[\n\r\0]/g,"");
    //console.log(''+portString);
    setTimeout(function() {
	    sensorObj = JSON.parse(portString);
	    //console.log('parsed');
	    var ACDBObj = JSON.parse(fs.readFileSync(sensorFilePath));
	    //console.log('Read database');
        ACDBObj.ACVals[1].Sensors = sensorObj;
	    //console.log('Added Sensors!');
        var ACDBStr = JSON.stringify(ACDBObj);
        fs.writeFileSync(sensorFilePath, ACDBStr);
	    //console.log('Wrote to Database!');
    }, 10);
  });
  portUSB2.write('R', function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    //console.log('ReadSens2 Sent');
    var SensorObj
    var portString = ''+portUSB2.read();
    portString = portString.replace(/[\n\r\0]/g,"");
    //console.log(''+portString);
    setTimeout(function() {
	    sensorObj = JSON.parse(portString);
	    //console.log('parsed');
	    var ACDBObj = JSON.parse(fs.readFileSync(sensorFilePath));
	    //console.log('Read database');
        ACDBObj.ACVals[2].Sensors = sensorObj;
	    //console.log('Added Sensors!');
        var ACDBStr = JSON.stringify(ACDBObj);
        fs.writeFileSync(sensorFilePath, ACDBStr);
	    //console.log('Wrote to Database!');
    }, 10);
  });
  portUSB3.write('R', function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    //console.log('ReadSens3 Sent');
    var SensorObj
    var portString = ''+portUSB3.read();
    portString = portString.replace(/[\n\r\0]/g,"");
    //console.log(''+portString);
    setTimeout(function() {
	    sensorObj = JSON.parse(portString);
	    //console.log('parsed');
	    var ACDBObj = JSON.parse(fs.readFileSync(sensorFilePath));
	    //console.log('Read database');
        ACDBObj.ACVals[3].Sensors = sensorObj;
	    //console.log('Added Sensors!');
        var ACDBStr = JSON.stringify(ACDBObj);
        fs.writeFileSync(sensorFilePath, ACDBStr);
	    //console.log('Wrote to Database!');
    }, 10);
  });
  setTimeout(syncMySHAS, 100);
  /*portUSB0.write('A', function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('ReadAC Sent');
  });*/
}

setInterval(syncData, 500);

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'pug');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

if (app.get('env') === 'development') {
  app.locals.pretty = true;
}

app.use('/', indexRouter);
app.use('/devices', devicesRouter);
app.use('/conf', confRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error', {title:err.status});
});

module.exports = app;
