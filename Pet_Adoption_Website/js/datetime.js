function updateDateTime() {
    const now = new Date();
    const dateTimeString = now.toLocaleString('en-US', {
        weekday: 'long',
        year: 'numeric',
        month: 'short',
        day: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit'
    });
    document.getElementById('current-datetime').textContent = dateTimeString;
}

// Update time every second
setInterval(updateDateTime, 1000);

// Initial call to set time immediately
updateDateTime();