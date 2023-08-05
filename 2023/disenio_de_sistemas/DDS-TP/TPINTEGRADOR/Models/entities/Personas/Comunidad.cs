
namespace TPINTEGRADOR.Models
{
    public class Comunidad : Identidad
    {
        public Comunidad(List<SuperServicio> intereses, int cantidadMiembrosAfectados, Persona administrador) 
        {
            Miembros = new List<Participacion>();
            Intereses = intereses;
            CantidadMiembrosAfectados = cantidadMiembrosAfectados;
            Administrador = administrador;
        }

        public List<Participacion> Miembros;
        public List<SuperServicio> Intereses;
        // public List<Incidente> Incidentes;
        public int CantidadMiembrosAfectados;
        public Persona Administrador;

        public void AvisoCambioLocalizacion(Persona persona)
        {  
            List<Incidente> incidentes = Intereses.SelectMany(interes => interes.Incidentes).ToList();
            incidentes = incidentes.Where(i => i.Localizacion == persona.LocalizacionActual).ToList();
            //incidentes.ForEach(i => sugerirInforme(persona,i));
        }

        public void AgregarUsuario(Persona persona, Rol rol, Medio medio)
        {
            Participacion participacion = new Participacion(persona, this, rol, medio);
            Miembros.Add(participacion);
            persona.Participaciones.Add(participacion);
            SistemaPersonas sistema = SistemaPersonas.GetInstance;
            sistema.Participaciones.Add(participacion);
        }

        public void EliminiarUsuario(int idPersona)
        {
            Participacion participacion = Miembros.Find(p => p.Persona.Id == idPersona);
            Miembros.Remove(participacion);
            participacion.Persona.Participaciones.Remove(participacion);
            SistemaPersonas sistema = SistemaPersonas.GetInstance;
            sistema.Participaciones.Remove(participacion);
        }

        public int calcularCantMiembrosAfectados()
        {
            return Miembros.Count(miembro => miembro.Rol == Rol.USUARIOAFECTADO);
        }

        public void NotificarMiembros(Incidente incidente)
        {
            foreach (var miembro in Miembros)
            {
                miembro.NotificarIncidente(incidente);
            }
        }
    }
}
