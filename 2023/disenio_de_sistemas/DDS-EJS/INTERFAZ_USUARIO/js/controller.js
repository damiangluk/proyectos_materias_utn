let typePassword = "password";

const changeType = () => {
    if (typePassword === "password") {
        typePassword = "text";
    } else {
        typePassword = "password";
    }
    document.getElementById("password").type = typePassword;
}

const enviarForm = () => {
    let username = document.getElementById("username").value;
    let password = document.getElementById("password").value;

    let usernameError = document.getElementById("usernameError");
    let passwordError = document.getElementById("passwordError");

    if (username === "") {
        usernameError.innerHTML = "El campo nombre de usuario es requerido.";
        return;
    } else {
        usernameError.innerHTML = "";
    }

    if (password === "") {
        passwordError.innerHTML = "El campo contraseña es requerido.";
        return;
    } else {
        passwordError.innerHTML = "";
    }

    if(username === "admin") {
        let genericError = document.getElementById("error");
        genericError.innerHTML = "El nombre de usuario no puede ser admin.";
        genericError.style.display = "block";
    } else if (password === "admin" || password === "1234"){
        let genericError = document.getElementById("error");
        genericError.innerHTML = "La contraseña ingresada es comun.";
        genericError.style.display = "block";
    } else {
        window.location.href = "logueado.html";
    }

    document.getElementById("submit").disabled = true;
    setTimeout(() => {
        document.getElementById("submit").disabled = false;
    }, 2000);
}