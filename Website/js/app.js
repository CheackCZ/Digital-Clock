/* Function that sets the time in the logo to the current time */
function updateClock() {
    var now = new Date();
    
    // Format the time as HH:MM:SS
    var time = now.getHours() + ':' + (now.getMinutes() < 10 ? '0' : '') + now.getMinutes();
    
    document.getElementById('time').textContent = time;
}

    // Call updateClock function every second
    setInterval(updateClock, 1000);

    updateClock();


/* Constants with the smaller display width parameters */
const mediaQuery = "(min-width: 320px) and (max-width: 925px)";
const mediaQueryS = "(min-width: 320px) and (max-width: 460px)";

var isOpened = false;

var nav = document.querySelector('nav');

/* Function, that closes the hamburger menu and uses animation defined in style.css */
function closeMenu() {
    if (window.matchMedia(mediaQuery).matches) {
        document.getElementById('menu-toggle').checked = false;

        nav.classList.remove('active');
        nav.classList.add('closing');
        
        nav.addEventListener('animationend', function handleAnimationEnd() {
            nav.style.display = 'none';
            nav.classList.remove('closing');
            nav.removeEventListener('animationend', handleAnimationEnd);
        });
        isOpened = false;
    }
}

/* Function, that opens the hamburger menu and uses animation defined in style.css */
function openMenu() {
    if (isOpened) {
       closeMenu();
       isOpened = false;
       return;
   }
   document.getElementById('menu-toggle').checked = true;
   
   nav.style.display = 'flex';

   if (window.matchMedia(mediaQuery).matches) {
       nav.classList.add('active');
   }
   
   isOpened = true;
}


/* Scrolling animation uses when clicked on the logo */
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
    var ul = this.document.getElementsByClassName('menu')[0];

    var first = document.getElementById('first-reference');


    if (window.scrollY >= 570) {
        if (window.matchMedia(mediaQuery).matches) {
            logo.classList.add('top-bg');
            menuIcon.classList.add('top-bg');
            if (window.matchMedia(mediaQueryS).matches) {
                ul.style.marginTop = '90px';
                ul.style.width = '80%';
                first.style.paddingTop = '30px';    
            } else {
                ul.style.marginTop = '100px';
                first.style.paddingTop = '20px';
                ul.style.width = '90%';
            }
        } else {
            logo.classList.add('top-bg');
            nav.classList.add('top-bg');

            ul.style.marginTop = '0';
            first.style.paddingTop = '0';
        }
    } else {
        logo.classList.remove('top-bg');
        menuIcon.classList.remove('top-bg');
        
        nav.classList.remove('top-bg');
        if (window.matchMedia(mediaQuery).matches) {
            ul.style.marginTop = '80px';
    
            first.style.paddingTop = '10px';
        } else {
            ul.style.marginTop = '0';
            first.style.paddingTop = '0';
        }
    }
});

/* Function that downloads the documentation, when clicked on. */
function downloadFile() {
    closeMenu();

    const link = document.createElement('a');
    link.href = 'docs/Documentation.docx';  
    link.download = 'Documentation.docx';  

    document.body.appendChild(link);

    link.click();

    document.body.removeChild(link);
}