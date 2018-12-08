
(function () {

  function init(){
    $('#submitButton').click(submitButtonHandler);
	setInterval(getSensorData(), 4000);
  }

  function submitButtonHandler (evt) {
     var testForm = document.getElementById('device_command_form');

      //prevent form submission
      evt.preventDefault();
      evt.stopPropagation();


      //make the AJAX call
      $.ajax({
        url: '/devices',
        type: 'POST',
        data: {
          commandFAC: testForm.commandFAC.value,
          commandLAV: testForm.commandLAV.value,
	      commandBEAC: testForm.commandBEAC.value,
	      commandBAAC: tectForm.commandBAAC.value
        }
      });
  }
  
  function getSensorData() {
	  $("#sensVals").load("/public/jsonobjects/actsensvalbd.json");
  }
  

//init on document ready
$(document).ready(init);
})();
