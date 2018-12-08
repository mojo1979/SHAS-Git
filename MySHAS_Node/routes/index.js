var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'MySHAS | Portal', pagetitle: 'MySHAS | Portal', pageMsg: 'MySHAS is a place to remotely manage your SHAS Control Hub! Sign in to start managing.' });
});

module.exports = router;
