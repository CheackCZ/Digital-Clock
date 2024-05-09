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