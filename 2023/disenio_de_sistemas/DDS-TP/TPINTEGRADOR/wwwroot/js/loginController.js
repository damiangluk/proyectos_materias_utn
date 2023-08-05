let typePassword = "password";

changeType = () => {
    if (typePassword === "password") {
        typePassword = "text";
    } else {
        typePassword = "password";
    }
    document.getElementById("password").type = typePassword;
}

disableButton = () => {
    document.getElementById("submit").disabled = true;
    setTimeout(() => {
        document.getElementById("submit").disabled = false;
    }, 2000);
}

LoginWithAuth = () => {
    var url = "/Login/LoginAuth";

    return new Promise((resolve, reject) => {

        $.ajax({
            url: url,
            type: 'POST',
            contentType: false,
            processData: false,
            success: function (response) {
            },
            error: function (xhr, status, error) {
                console.error(error);
            }
        });
    });
}

validateForm = () => {
    let username = document.getElementById("username").value;
    let password = document.getElementById("password").value;
    let isValid = true;

    let usernameError = document.getElementById("usernameError");
    let passwordError = document.getElementById("passwordError");

    if (username === "") {
        usernameError.innerHTML = "El campo nombre de usuario es requerido.";
        isValid = false;
    } else {
        usernameError.innerHTML = "";
    }

    if (password === "") {
        passwordError.innerHTML = "El campo contraseña es requerido.";
        isValid = false;
    } else {
        passwordError.innerHTML = "";
    }

    return isValid;
}