(function() {
    // Set the configuration for your app
    var config = {
        apiKey: "AIzaSyA5cs4hMyxEeYybA844KyBgR4vNncw6eHs",
        authDomain: "wardio42.firebaseapp.com",
        databaseURL: "https://wardio42.firebaseio.com",
        storageBucket: "wardio42.appspot.com",
        messagingSenderId: "898879733249"
    };

    firebase.initializeApp(config);
    
    var database = firebase.database();

    // Get element from the DOM
    const bpmElement = document.getElementById ('BPM');
    const spo2Element = document.getElementById ('SpO2');
    const tempElement = document.getElementById ('Temperatura');

    // Create BPM database reference
    const bpmRef = database.ref('BPM');
    
    // Create SpO2 database reference
    const spo2Ref = database.ref('SpO2');
    
    // Create temperature database reference
    const tempRef = database.ref('Temperatura');
    
    // Sync objects changes
    bpmRef.limitToLast(1).on('value', function(snapshot) {
        snapshot.forEach(function(childSnapshot) {
            var childData = childSnapshot.val();
            console.log("BPM: " + childData);
            bpmElement.innerText = childData;
        });
    });
    spo2Ref.limitToLast(1).on('value', function(snapshot) {
        snapshot.forEach(function(childSnapshot) {
            var childData = childSnapshot.val();
            console.log("SpO2: " + childData);
            spo2Element.innerText = childData;
        });
    });
        tempRef.limitToLast(1).on('value', function(snapshot) {
        snapshot.forEach(function(childSnapshot) {
            var childData = childSnapshot.val();
            console.log("Temperatura: " + childData);
            tempElement.innerText = childData;
        });
    });

}());
