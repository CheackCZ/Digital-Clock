/* Function setting the time in clock logo to the current time */
function updateClock() {
    // Create a new Date object
    var now = new Date();
    
    // Format the time as HH:MM:SS
    var time = now.getHours() + ':' + (now.getMinutes() < 10 ? '0' : '') + now.getMinutes();
    
    // Update the clock display
    document.getElementById('time').textContent = time;
}
// Call updateClock function every second
setInterval(updateClock, 1000);
// Initial call to display the time immediately
updateClock();


var isOpened = false;
var nav = document.querySelector('nav');

//Animation, closing the hamburger menu when item is selected
function closeMenu() {
    document.getElementById('menu-toggle').checked = false;

    nav.style.display = 'none';

    isOpened = false;
}

function openMenu() {
    if (isOpened) {
        closeMenu();
        isOpened = false;
        return;
    }
    document.getElementById('menu-toggle').checked = true;

    nav.style.display = 'flex';

    isOpened = true;
}


/* Method controlling the width of the screen */
function checkWidthAndDisplayNav() {
    // Check if the viewport width is equal to or greater than 925 pixels
    if (window.innerWidth >= 925) {
        nav.style.display = 'flex'; // Display the navigation
    } else {
        nav.style.display = 'none'; // Hide the navigation
    }
}

// Add event listener for resize event
window.addEventListener('resize', function() {
    // Call the function to check width and update navigation display
    checkWidthAndDisplayNav();
});

// Call the function initially to set navigation display based on initial width
checkWidthAndDisplayNav();


/* Scrolling animation */
function scrollToTop() {
  window.scrollTo({
      top: 0,
      behavior: 'smooth'
  });
}

/* Function that makes navbar and logo background, when is scrolled bellow the header. */
window.addEventListener('scroll', function() {
    var logo = document.getElementById('logo');
    var nav = document.querySelector('nav');

    var menuIcon = document.querySelector('.menu-button-container');

    const mediaQuery = "(min-width: 320px) and (max-width: 925px)";

    if (window.scrollY >= 570) {

        if (window.matchMedia(mediaQuery).matches) {
            logo.classList.add('top-bg');
            menuIcon.classList.add('top-bg');
        } else {
            logo.classList.add('top-bg');
            nav.classList.add('top-bg');
        }
    } else {
        logo.classList.remove('top-bg');
        menuIcon.classList.remove('top-bg');
        nav.classList.remove('top-bg');
    }
});