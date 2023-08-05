var rowsError = "";
var organismos;
var provinciasResult;
var municipiosResult;
var departamentosResult;
var importButton = document.getElementById('importButton');
var textImport = document.getElementById('textButton');
var loadingImport = document.getElementById('loadingButton');

validarArchivo = async () => {
    var inputFile = document.getElementById('formFile');
    var file = inputFile.files[0];
    var allowedExtensions = /(\.csv)$/i;

    if (file == null) {
        alert('Por favor, cargue algun archivo.');
        return false;
    }

    if (!allowedExtensions.exec(file.name)) {
        alert('Por favor, selecciona un archivo CSV válido.');
        return false;
    }

    importButton.disabled = true
    textImport.style.display = 'none';
    loadingImport.style.display = 'flex';

    rowsError = "";

    await enviarArchivo(file);
    var msj = document.getElementById('msg');
    msj.innerHTML = '';
    var tabla = crearTabla();
    cargarInformacion(tabla);

    var tableContainer = document.getElementById('tableContainer');
    tableContainer.innerHTML = '';
    tableContainer.appendChild(tabla);
    inputFile.value = "";
}

crearTabla = () => {
    var tabla = document.createElement('table');
    tabla.classList.add('table', 'table-bordered', 'table-striped', 'table-hover');

    var encabezado = document.createElement('tr');

    var tipoOrganismoHeader = document.createElement('th');
    tipoOrganismoHeader.textContent = 'Tipo de organismo';
    encabezado.appendChild(tipoOrganismoHeader);

    var nombreOrganismoHeader = document.createElement('th');
    nombreOrganismoHeader.textContent = 'Nombre de organismo';
    encabezado.appendChild(nombreOrganismoHeader);

   /* var entidadHeader = document.createElement('th');
    entidadHeader.textContent = 'Entidad';
    encabezado.appendChild(entidadHeader);

    var entidadTipoHeader = document.createElement('th');
    entidadTipoHeader.textContent = 'Encargado';
    encabezado.appendChild(entidadTipoHeader);

    var LocalizacionesHeader = document.createElement('th');
    LocalizacionesHeader.textContent = 'Localizaciones';
    encabezado.appendChild(LocalizacionesHeader);

    var tipoLocalizacionHeader = document.createElement('th');
    tipoLocalizacionHeader.textContent = 'Tipo de localizacion';
    encabezado.appendChild(tipoLocalizacionHeader);

    var nombreLocalizacionHeader = document.createElement('th');
    nombreLocalizacionHeader.textContent = 'Nombre localizacion';
    encabezado.appendChild(nombreLocalizacionHeader);

    var encargadoNombreHeader = document.createElement('th');
    encargadoNombreHeader.textContent = 'Nombre encargado';
    encabezado.appendChild(encargadoNombreHeader);
    
    var encargadoApellidoHeader = document.createElement('th');
    encargadoApellidoHeader.textContent = 'Apellido encargado';
    encabezado.appendChild(encargadoApellidoHeader);

    var encargadoCorreoElectronicoHeader = document.createElement('th');
    encargadoCorreoElectronicoHeader.textContent = 'Correo electronico encargado';
    encabezado.appendChild(encargadoCorreoElectronicoHeader);

    var encargadoContraseniaHeader = document.createElement('th');
    encargadoContraseniaHeader.textContent = 'Contraseña encargado';
    encabezado.appendChild(encargadoContraseniaHeader);
    */

    tabla.appendChild(encabezado);
    return tabla;
}

cargarInformacion = (tabla) => {
    for (var i = 0; i < organismos.length; i++) {
        var tipoOrganismo = organismos[i].tipoOrganismo.trim();
        var nombreOrganismo = organismos[i].nombreOrganismo.trim();

       /* var entidad = organismos[i].EntidadNombre.trim();
        var entidadTipo = organismos[i].TipoEntidad.trim();
        var localizaciones = '';
        for (var j = 0; i < organismos[i].localizaciones.length; i++) {
            localizaciones += organismos[i].localizaciones[j].trim();
        }
        //var tipoLocalizacion = organismos[i].TipoLocalizacion.trim();
        //var nombreLocalizacion = organismos[i].NombreLocalizacion.trim();
        var encargadoNombre = organismos[i].EncargadoNombre.trim();
        var encargadoApellido = organismos[i].EncargadoApellido.trim();
        var encargadoCorreoElectronico = organismos[i].EncargadoCorreoElectronico.trim();
        var encargadoContrasenia = organismos[i].EncargadoContrasenia.trim();
        */

        var fila = document.createElement('tr');

        var tipoOrganismoTd = document.createElement('td');
        tipoOrganismoTd.textContent = tipoOrganismo;
        fila.appendChild(tipoOrganismoTd);

        var nombreOrganismoTd = document.createElement('td');
        nombreOrganismoTd.textContent = nombreOrganismo;
        fila.appendChild(nombreOrganismoTd);

       /* var entidadTd = document.createElement('td');
        entidadTd.textContent = entidad;
        fila.appendChild(entidadTd);

        var entidadTipoTd = document.createElement('td');
        entidadTipoTd.textContent = entidadTipo;
        fila.appendChild(entidadTipoTd);

        var tipoLocalizacionTd = document.createElement('td');
        tipoLocalizacionTd.textContent = tipoLocalizacion;
        fila.appendChild(tipoLocalizacionTd);

        var nombreLocalizacionTd = document.createElement('td');
        nombreLocalizacionTd.textContent = nombreLocalizacion;
        fila.appendChild(nombreLocalizacionTd);

        var encargadoNombreTd = document.createElement('td');
        encargadoNombreTd.textContent = encargadoNombre;
        fila.appendChild(encargadoNombreTd);

        var encargadoApellidoTd = document.createElement('td');
        encargadoApellidoTd.textContent = encargadoApellido;
        fila.appendChild(encargadoApellidoTd);

        var encargadoCorreoElectronicoTd = document.createElement('td');
        encargadoCorreoElectronicoTd.textContent = encargadoCorreoElectronico;
        fila.appendChild(encargadoCorreoElectronicoTd);

        var encargadoContraseniaTd = document.createElement('td');
        encargadoContraseniaTd.textContent = encargadoContrasenia;
        fila.appendChild(encargadoContraseniaTd);
        */

        tabla.appendChild(fila);
    }

    if (rowsError !== "") {
        var msj = document.getElementById('msg');
        msj.innerHTML = rowsError;
    }
}

enviarArchivo = (file) => {

    var formData = new FormData();
    formData.append('archivoCSV', file);

    return new Promise((resolve, reject) => {

        $.ajax({
            url: '/Organismos/ValidarArchivo',
            type: 'POST',
            contentType: false,
            processData: false,
            data: formData,
            success: function (response) {
                var result = JSON.parse(response);
                if (result.validation) {
                    organismos = result.content.organismos;
                    rowsError = result.content.rowsError;

                    importButton.disabled = false
                    textImport.style.display = 'flex';
                    loadingImport.style.display = 'none';

                    resolve();
                } else {
                    console.log("Ocurrio un error", result);
                    var msj = document.getElementById('msg');
                    msj.innerHTML = result.message;

                    importButton.disabled = false
                    textImport.style.display = 'flex';
                    loadingImport.style.display = 'none';

                    reject("Ocurrió un error en la consulta API");
                }
            },
            error: function (xhr, status, error) {
                console.error(error);
                importButton.disabled = false
                textImport.style.display = 'flex';
                loadingImport.style.display = 'none';
                reject("Ocurrió un error en la consulta API");
            }
        });
    });
}