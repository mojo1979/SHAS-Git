var menuButton = document.getElementById('display_menu_button');
var menuDisplay = document.getElementById('display_menu');
var viewportDisplay = document.getElementById('display_viewport');

menuButton.style.cursor = 'pointer';
menuButton.onclick = function() {
	var left = window.getComputedStyle(menuDisplay).getPropertyValue('left');
	if (left === '-350px') {
		openMenu();
	} else {
		closeMenu();
	}
};

//viewportDisplay.onclick = closeMenu();

function openMenu() {
	menuDisplay.style.animation = 'open_menu 0.3s';
	menuDisplay.style.left = '0px';
	menuButton.style.background = "rgba(120,160,220,1) url('/images/chevron-left-white.png') no-repeat center center";
	menuButton.style.backgroundSize = '25px 25px';
}

function closeMenu() {
	menuDisplay.style.animation = 'close_menu 0.3s';
	menuDisplay.style.left = '-350px';
	menuButton.style.background = "rgba(120,160,220,1) url('/images/chevron-right-white.png') no-repeat center center";
	menuButton.style.backgroundSize = '25px 25px';
}