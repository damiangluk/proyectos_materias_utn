
namespace TPINTEGRADOR.Models
{
    public class Incidente : Identidad
    {
        public Incidente(SuperServicio servicio, DateTime fechaApertura, DateTime fechaCierre, Localizacion localizacion, string informe, string estado)
        {
            Servicio = servicio;
            FechaApertura = fechaApertura;
            FechaCierre = fechaCierre;
            Localizacion = localizacion;
            Informe = informe;
            Estado = estado;
        }

        public SuperServicio Servicio;
        public DateTime FechaApertura;
        public DateTime? FechaCierre;
        public Localizacion Localizacion;
        public string Informe;
        public string Estado;

        public bool EstaAbierto()
        {
            return !FechaCierre.HasValue;
        }

        public int CalcularTiempoDeCierre()
        {
            TimeSpan diferencia = FechaCierre.Value - FechaApertura;
            return (int)diferencia.TotalSeconds;
        }

    }
}