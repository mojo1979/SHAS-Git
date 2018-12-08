var express = require('express');
var router = express.Router();

/* GET devices page. */
router.get('/', function(req, res, next) {
  res.render('page', { title: 'MySHAS Connection', data: 'Not ready yet.' });
});

module.exports = router;
