function controllerBtnHandler () {
    const urlParams = new URLSearchParams(window.location.search);
    const MySHASId = document.getElementById('myshas_id').innerHTML;
    const  sessionId = urlParams.get('session');
    window.open("controller?session="+sessionId+"&key="+MySHASId, "_self");
}

function logoutBtnHandler () {
    const urlParams = new URLSearchParams(window.location.search);
    const  sessionId = urlParams.get('session');
    window.open("logout?session="+sessionId, "_self");
}
