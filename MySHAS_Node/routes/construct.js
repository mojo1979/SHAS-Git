var express = require('express');
var router = express.Router();

/* GET users listing. */
router.get('/', function(req, res, next) {
   res.render('construct', { title: 'MySHAS | Under Construction', pagetitle: 'Under Construction' });
});

module.exports = router;
