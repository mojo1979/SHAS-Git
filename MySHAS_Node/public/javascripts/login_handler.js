(function () {

  function init(){
    $('#submitButton').click(submitButtonHandler);
  }

  function submitButtonHandler (evt) {
     var loginForm = document.getElementById('myshas_login_form');

      //prevent form submission
      evt.preventDefault();
      evt.stopPropagation();


      //make the AJAX call
    if (loginForm.user_id.value === "") {
      $(#login_form_message).html('<h1>User ID can\'t be empty!</h1>');
    } else {
      $.ajax({
        url: '/login',
        type: 'POST',
        data: {
          user_id: loginForm.user_id.value,
          user_pass: loginForm.user_pass.value
        }
      });
    }
  }

  //init on document ready
  $(document).ready(init);
})();

