document.addEventListener('DOMContentLoaded', function() {
    const giveawayForm = document.getElementById('giveaway-pet-form');
    
    giveawayForm.addEventListener('submit', function(event) {
        event.preventDefault();
        
        // Get all form fields
        const fields = giveawayForm.querySelectorAll('input, select, textarea');
        let isValid = true;
        let errorMessage = 'Please correct the following:\n';
        
        fields.forEach(field => {
            // Check if field is empty
            if (!field.value.trim()) {
                isValid = false;
                errorMessage += `- ${field.name || field.id} is required\n`;
            }
            
            // Email validation
            if (field.type === 'email') {
                const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
                if (!emailRegex.test(field.value)) {
                    isValid = false;
                    errorMessage += '- Invalid email format\n';
                }
            }
        });
        
        if (!isValid) {
            alert(errorMessage);
        } else {
            alert('Form submitted successfully!');
            // In a real application, you would send this data to a server
        }
    });
});