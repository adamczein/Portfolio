// This script can be used to dynamically add interactivity to the browse pets page
document.addEventListener('DOMContentLoaded', function() {
    const interestedButtons = document.querySelectorAll('.interested-btn');
    
    interestedButtons.forEach(button => {
        button.addEventListener('click', function() {
            alert('Thank you for your interest! We will contact you soon.');
        });
    });
});