
(function () {

  function init(){
    $('#submitButtonConf').click(submitButtonHandler2);
  }

  function submitButtonHandler2 (evt) {
     var testForm2 = document.getElementById('config_form');

      //prevent form submission
      evt.preventDefault();
      evt.stopPropagation();


      //make the AJAX call
      $.ajax({
        url: '/conf',
        type: 'POST',
        data: {
          postDevName: testForm2.confDevName.value,
          postDevId: testForm2.confDevId.value,
	  postMySHAS: testForm2.confMySHAS.value
        }
      });
  }

//init on document ready
$(document).ready(init);
})();
