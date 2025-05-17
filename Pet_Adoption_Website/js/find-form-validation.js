document.addEventListener('DOMContentLoaded', function() {
    const findForm = document.getElementById('find-pet-form');
    
    findForm.addEventListener('submit', function(event) {
        event.preventDefault();
        
        // Get all form fields
        const fields = findForm.querySelectorAll('select, input[type="radio"]:checked');
        let isValid = true;
        let errorMessage = 'Please fill out all fields:\n';
        
        fields.forEach(field => {
            if (!field.value) {
                isValid = false;
                errorMessage += `- ${field.name || field.id}\n`;
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