namespace TPINTEGRADOR.Models
{

    public sealed class SistemaServicios
    {
        #region instance
        private static readonly SistemaServicios instance = new SistemaServicios();

        private SistemaServicios() { }

        public static SistemaServicios GetInstance
        {
            get { return instance; }
        }
        #endregion

        #region properties

        public List<Incidente> Incidentes { get; set; } = new List<Incidente>();
        public List<SuperServicio> Servicios { get; set; } = new List<SuperServicio>();
        #endregion

        #region methods

        public void CrearIncidente(Incidente incidente, int idServicio)
        {   
            SuperServicio servicio = Servicios.Find(s => s.Id == idServicio);
            incidente.Servicio = servicio;
            Incidentes.Add(incidente);
            servicio.Incidentes.Add(incidente);
            servicio.Comunidades.ForEach(c => c.NotificarMiembros(incidente));
        }

        public void CerrarIncidente(int idIncidente)
        {      
            Incidente incidente = Incidentes.Find(i => i.Id == idIncidente);
            incidente.FechaCierre = DateTime.Now;
        }
        
        public List<Incidente> ConsultarIncidentePorEstado(bool? estado)
        {
            if(!estado.HasValue)
                return Incidentes;

            return Incidentes.Where(i => i.EstaAbierto() == estado).ToList();
        }

        public List<Entidad> RankingEntidadesTiempoPromedioIncidentesParaProveedor(ProveedorDeServicio proveedor)
        {
            var incidentesNecesarios = Incidentes.Where(i => i.Servicio.Proveedor.Equals(proveedor) && !i.EstaAbierto() && (DateTime.Now - i.FechaApertura).TotalDays <= 7).ToList();
            var diccionario = AgruparIncidentesPorEntidad(incidentesNecesarios);
            return diccionario.Keys.OrderByDescending(e => diccionario[e].Average(e => e.CalcularTiempoDeCierre())).ToList();
        }


        public List<Entidad> RankingEntidadesMayorCantidadIncidentesParaProveedor(ProveedorDeServicio proveedor)
        {
            var incidentesNecesarios = Incidentes.Where(i => i.Servicio.Proveedor.Equals(proveedor) && (!i.EstaAbierto() || (DateTime.Now - i.FechaApertura).TotalHours > 24) && (DateTime.Now - i.FechaApertura).TotalDays <= 7).ToList();
            var diccionario = AgruparIncidentesPorEntidad(incidentesNecesarios);
            return diccionario.Keys.OrderByDescending(e => diccionario[e].Count()).ToList();
        }

        public List<Entidad> RankingEntidadesTiempoPromedioIncidentesParaOrganismo(Organismo organismo)
        {
            var incidentesNecesarios = organismo.Entidades.SelectMany(e => e.Servicios).SelectMany(s => s.Incidentes)
                .Where(i => !i.EstaAbierto() && (DateTime.Now - i.FechaApertura).TotalDays <= 7).ToList();
            var diccionario = AgruparIncidentesPorEntidad(incidentesNecesarios);
            return diccionario.Keys.OrderByDescending(e => diccionario[e].Average(e => e.CalcularTiempoDeCierre())).ToList();
        }


        public List<Entidad> RankingEntidadesMayorCantidadIncidentesParaOrganismo(Organismo organismo)
        {
            var incidentesNecesarios = organismo.Entidades.SelectMany(e => e.Servicios).SelectMany(s => s.Incidentes)
                .Where(i => (!i.EstaAbierto() || (DateTime.Now - i.FechaApertura).TotalHours > 24) && (DateTime.Now - i.FechaApertura).TotalDays <= 7).ToList();
            var diccionario = AgruparIncidentesPorEntidad(incidentesNecesarios);
            return diccionario.Keys.OrderByDescending(e => diccionario[e].Count()).ToList();
        }

        private Dictionary<Entidad, List<Incidente>> AgruparIncidentesPorEntidad(List<Incidente> incidentes)
        {
            Dictionary<Entidad, List<Incidente>> diccionario = new Dictionary<Entidad, List<Incidente>>();

            foreach (var incidente in incidentes)
            {
                foreach (var entidad in incidente.Servicio.Entidades)
                {
                    if (!diccionario.ContainsKey(entidad))
                    {
                        diccionario[entidad] = new List<Incidente>();
                    }

                    diccionario[entidad].Add(incidente);
                }
            }

            return diccionario;
        }

        #endregion
    }
}