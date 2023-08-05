-- CREACION DE TABLAS

create table LOS_DEBATIENTES.BI_periodos (
	per_id decimal(18, 0) not null identity(1,1),
	per_anio int not null,
	per_mes int not null
)

create table LOS_DEBATIENTES.BI_dias (
	dia_id decimal(18, 0) not null identity(1,1),
	dia_descripcion nvarchar(50) not null,
	dia_numero int not null
)

create table LOS_DEBATIENTES.BI_rangos_horarios (
	rho_id decimal(18, 0) not null identity(1,1),
	rho_inicio int not null,
	rho_fin int not null
)

create table LOS_DEBATIENTES.BI_estados_reclamos (
	ere_id decimal(18, 0) not null identity(1,1),
	ere_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.BI_estados_pedidos (
	epe_id decimal(18, 0) not null identity(1,1),
	epe_descripcion nvarchar(50) not null,
)

create table LOS_DEBATIENTES.BI_rangos_etarios (
	ret_id decimal(18, 0) not null identity(1,1),
	ret_inicio int not null,
	ret_fin int not null
)

create table LOS_DEBATIENTES.BI_tipos_paquete (
	tpa_id decimal(18, 0) not null identity(1,1),
	tpa_tipo nvarchar(50) not null
)

create table LOS_DEBATIENTES.BI_tipos_movilidad (
	tmo_id decimal(18, 0) not null identity(1,1),
	tmo_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.BI_estados_envios_mensajeria (
	eem_id decimal(18, 0) not null identity(1,1),
	eem_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.BI_tipos_pago (
	tpg_id decimal(18, 0) not null identity(1,1),
	tpg_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.BI_localidades (
	loc_id decimal(18, 0) not null identity(1,1),
	loc_localidad nvarchar(255) not null,
	loc_provincia nvarchar(255) not null
)

create table LOS_DEBATIENTES.BI_tipos_local (
	tlo_id decimal(18, 0) not null identity(1,1),
	tlo_descripcion nvarchar(50) not null,
)

create table LOS_DEBATIENTES.BI_locales (
	lok_id decimal(18, 0) not null identity(1,1),
	lok_nombre nvarchar(100) not null,
	lok_descripcion nvarchar(255) not null,
	lok_direccion nvarchar(255) not null
)

create table LOS_DEBATIENTES.BI_tipos_reclamo (
	tre_id decimal(18, 0) not null identity(1,1),
	tre_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.BI_pedidos (
	p_periodo decimal(18, 0) not null,
	p_dia decimal(18, 0) not null,
	p_rango_horario decimal(18, 0) not null,
	p_localidad decimal(18, 0) not null,
	p_rango_etario_usuario decimal(18, 0) not null,
	p_rango_etario_repartidor decimal(18, 0) not null,
	p_tipo_pago decimal(18, 0) not null,
	p_local decimal(18, 0) not null,
	p_tipo_local decimal(18, 0) not null,
	p_tipo_movilidad decimal(18, 0) not null,
	p_estado_pedido decimal(18, 0) not null,
	p_cantidad_pedidos decimal(18, 2) not null,
	p_montos_no_cobrados decimal(18,2) not null,
	p_precio_envios decimal(18,2) not null,
	p_tiempo_de_entregas decimal(18, 2) not null,
	p_monto_cupones decimal(18, 2) not null,
	p_calificaciones decimal(18, 0) not null
)

create table LOS_DEBATIENTES.BI_reclamos (
	r_periodo decimal(18, 0) not null,
	r_dia decimal(18, 0) not null,
	r_rango_horario decimal(18, 0) not null,
	r_rango_etario_operario decimal(18, 0) not null,
	r_local decimal(18, 0) not null,
	r_estado_reclamo decimal(18, 0) not null,
	r_tipo_reclamo decimal(18, 0) not null,
	r_cantidad_reclamos decimal(18, 2) not null,
	r_tiempos_de_resolucion decimal(18, 2) not null,
	r_calificaciones decimal(18, 0) not null,
	r_montos_cupones decimal(18, 0) not null,
)

create table LOS_DEBATIENTES.BI_mensajerias (
	m_periodo decimal(18, 0) not null,
	m_dia decimal(18, 0) not null,
	m_rango_horario decimal(18, 0) not null,
	m_localidad decimal(18, 0) not null, 
	m_rango_etario_usuario decimal(18, 0) not null,
	m_rango_etario_repartidor decimal(18, 0) not null,
	m_tipo_pago decimal(18, 0) not null,
	m_tipo_movilidad decimal(18, 0) not null,
	m_tipo_paquete decimal(18, 0) not null,
	m_estado_mensajeria decimal(18, 0) not null,
	m_valores_asegurados decimal(18, 2) not null,
	m_tiempo_de_entregas decimal(18, 2) not null,
	m_cantidad_envios decimal(18,2) not null
)

-- CREACION DE PRIMARY KEY

alter table LOS_DEBATIENTES.BI_periodos add constraint pk_per_id primary key (per_id)
alter table LOS_DEBATIENTES.BI_dias	add constraint pk_dia_id primary key (dia_id)
alter table LOS_DEBATIENTES.BI_rangos_horarios add constraint pk_rho_id primary key (rho_id)
alter table LOS_DEBATIENTES.BI_estados_reclamos add constraint pk_ere_id primary key (ere_id)
alter table LOS_DEBATIENTES.BI_estados_pedidos add constraint pk_epe_id primary key (epe_id)
alter table LOS_DEBATIENTES.BI_rangos_etarios	add constraint pk_ret_id primary key (ret_id)
alter table LOS_DEBATIENTES.BI_tipos_paquete add constraint pk_tpa_id primary key (tpa_id)
alter table LOS_DEBATIENTES.BI_tipos_movilidad add constraint pk_tmo_id primary key (tmo_id)
alter table LOS_DEBATIENTES.BI_estados_envios_mensajeria add constraint pk_eem_id primary key (eem_id)
alter table LOS_DEBATIENTES.BI_tipos_pago add constraint pk_tpg_id primary key (tpg_id)
alter table LOS_DEBATIENTES.BI_localidades add constraint pk_loc_id primary key (loc_id)
alter table LOS_DEBATIENTES.BI_tipos_local add constraint pk_tlo_id primary key (tlo_id)
alter table LOS_DEBATIENTES.BI_locales add constraint pk_lok_id primary key (lok_id)
alter table LOS_DEBATIENTES.BI_tipos_reclamo add constraint pk_tre_id primary key (tre_id)

-- CREACION DE FOREIGN KEY

-- FK PEDIDOS
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_periodo foreign key (p_periodo) references LOS_DEBATIENTES.BI_periodos (per_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_dia foreign key (p_dia) references LOS_DEBATIENTES.BI_dias (dia_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_rango_horario foreign key (p_rango_horario) references LOS_DEBATIENTES.BI_rangos_horarios (rho_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_localidad foreign key (p_localidad) references LOS_DEBATIENTES.BI_localidades (loc_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_rango_etario_usuario foreign key (p_rango_etario_usuario) references LOS_DEBATIENTES.BI_rangos_etarios (ret_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_rango_etario_repartidor foreign key (p_rango_etario_repartidor) references LOS_DEBATIENTES.BI_rangos_etarios (ret_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_tipo_pago foreign key (p_tipo_pago) references LOS_DEBATIENTES.BI_tipos_pago (tpg_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_local foreign key (p_local) references LOS_DEBATIENTES.BI_locales (lok_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_tipo_local foreign key (p_tipo_local) references LOS_DEBATIENTES.BI_tipos_local (tlo_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_tipo_movilidad foreign key (p_tipo_movilidad) references LOS_DEBATIENTES.BI_tipos_movilidad (tmo_id)
alter table LOS_DEBATIENTES.BI_pedidos add constraint fk_p_estado_pedido foreign key (p_estado_pedido) references LOS_DEBATIENTES.BI_estados_pedidos (epe_id)

-- FK MENSAJERIAS
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_periodo foreign key (m_periodo) references LOS_DEBATIENTES.BI_periodos (per_id)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_dia foreign key (m_dia) references LOS_DEBATIENTES.BI_dias (dia_id)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_rango_horario foreign key (m_rango_horario) references LOS_DEBATIENTES.BI_rangos_horarios (rho_id)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_localidad foreign key (m_localidad) references LOS_DEBATIENTES.BI_localidades (loc_id)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_rango_etario_usuario foreign key (m_rango_etario_usuario) references LOS_DEBATIENTES.BI_rangos_etarios (ret_id)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_rango_etario_repartidor foreign key (m_rango_etario_repartidor) references LOS_DEBATIENTES.BI_rangos_etarios (ret_id)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_tipo_pago foreign key (m_tipo_pago) references LOS_DEBATIENTES.BI_tipos_pago (tpg_id)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_tipo_paquete foreign key (m_tipo_paquete) references LOS_DEBATIENTES.BI_tipos_paquete (tpa_id)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_tipo_movilidad foreign key (m_tipo_movilidad) references LOS_DEBATIENTES.BI_tipos_movilidad (tmo_id)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint fk_m_estado_mensajeria foreign key (m_estado_mensajeria) references LOS_DEBATIENTES.BI_estados_envios_mensajeria (eem_id)

-- FK RECLAMOS
alter table LOS_DEBATIENTES.BI_reclamos add constraint fk_r_periodo foreign key (r_periodo) references LOS_DEBATIENTES.BI_periodos (per_id)
alter table LOS_DEBATIENTES.BI_reclamos add constraint fk_r_dia foreign key (r_dia) references LOS_DEBATIENTES.BI_dias (dia_id)
alter table LOS_DEBATIENTES.BI_reclamos add constraint fk_r_rango_horario foreign key (r_rango_horario) references LOS_DEBATIENTES.BI_rangos_horarios (rho_id)
alter table LOS_DEBATIENTES.BI_reclamos add constraint fk_r_rango_etario_operario foreign key (r_rango_etario_operario) references LOS_DEBATIENTES.BI_rangos_etarios (ret_id)
alter table LOS_DEBATIENTES.BI_reclamos add constraint fk_r_local foreign key (r_local) references LOS_DEBATIENTES.BI_locales (lok_id)
alter table LOS_DEBATIENTES.BI_reclamos add constraint fk_r_estado_reclamo foreign key (r_estado_reclamo) references LOS_DEBATIENTES.BI_estados_reclamos (ere_id)
alter table LOS_DEBATIENTES.BI_reclamos add constraint fk_r_tipo_reclamo foreign key (r_tipo_reclamo) references LOS_DEBATIENTES.BI_tipos_reclamo (tre_id)

-- CREACION DE UNIQUES

alter table LOS_DEBATIENTES.BI_locales add constraint uc_BI_locales unique (lok_nombre, lok_direccion)
alter table LOS_DEBATIENTES.BI_tipos_local add constraint uc_lok_descripcion unique (tlo_descripcion)
alter table LOS_DEBATIENTES.BI_tipos_pago add constraint uc_tpg_descripcion unique (tpg_descripcion)
alter table LOS_DEBATIENTES.BI_estados_envios_mensajeria add constraint uc_eem_descripcion unique (eem_descripcion)
alter table LOS_DEBATIENTES.BI_tipos_movilidad add constraint uc_tmo_descripcion unique (tmo_descripcion)
alter table LOS_DEBATIENTES.BI_tipos_paquete add constraint uc_tpa_tipo unique (tpa_tipo)
alter table LOS_DEBATIENTES.BI_rangos_etarios add constraint uc_ret_rangos_etarios unique (ret_inicio, ret_fin)
alter table LOS_DEBATIENTES.BI_estados_pedidos add constraint uc_epe_descripcion unique (epe_descripcion)
alter table LOS_DEBATIENTES.BI_estados_reclamos add constraint uc_ere_descripcion unique (ere_descripcion)
alter table LOS_DEBATIENTES.BI_rangos_horarios add constraint uc_rangos_horarios unique (rho_inicio, rho_fin)
alter table LOS_DEBATIENTES.BI_dias add constraint uc_BI_dia_descripcion unique (dia_descripcion)
alter table LOS_DEBATIENTES.BI_periodos add constraint uc_periodos unique (per_anio, per_mes)
alter table LOS_DEBATIENTES.BI_tipos_reclamo add constraint uc_tipos_reclamo unique (tre_descripcion)
alter table LOS_DEBATIENTES.BI_mensajerias add constraint uc_mensajerias unique (m_periodo, m_dia, m_rango_horario, m_localidad,  m_rango_etario_usuario, m_rango_etario_repartidor, m_tipo_pago, m_tipo_movilidad, m_tipo_paquete, m_estado_mensajeria)
alter table LOS_DEBATIENTES.BI_reclamos add constraint uc_reclamos unique (r_periodo, r_dia, r_rango_horario, r_rango_etario_operario, r_local, r_estado_reclamo, r_tipo_reclamo)
alter table LOS_DEBATIENTES.BI_pedidos add constraint uc_pedidos unique (p_periodo, p_dia, p_rango_horario, p_localidad, p_rango_etario_usuario, p_rango_etario_repartidor, p_tipo_pago, p_local, p_tipo_local, p_tipo_movilidad, p_estado_pedido)

-- CREACION DE CHECKS

alter table LOS_DEBATIENTES.BI_periodos add constraint chk_per_mes check (per_mes > 0 and per_mes < 13)
alter table LOS_DEBATIENTES.BI_rangos_horarios add constraint chk_rho_inicio check (rho_inicio >= 0 and rho_inicio < 24)
alter table LOS_DEBATIENTES.BI_rangos_horarios add constraint chk_rho_fin check (rho_fin >= 0 and rho_fin < 24)
alter table LOS_DEBATIENTES.BI_rangos_etarios add constraint chk_ret_inicio check (ret_inicio >= 0)
alter table LOS_DEBATIENTES.BI_rangos_etarios add constraint chk_ret_fin check (ret_fin >= 0)

-- CREACION DE INDICES

create index i_localidades ON LOS_DEBATIENTES.BI_localidades (loc_localidad)
create index i_locales ON LOS_DEBATIENTES.BI_locales (lok_nombre, lok_direccion)
create index i_tipos_local ON LOS_DEBATIENTES.BI_tipos_local (tlo_descripcion)
create index i_tipos_pago ON LOS_DEBATIENTES.BI_tipos_pago (tpg_descripcion)
create index i_estados_envios_mensajeria ON LOS_DEBATIENTES.BI_estados_envios_mensajeria (eem_descripcion)
create index i_tipos_paquete ON LOS_DEBATIENTES.BI_tipos_paquete (tpa_tipo)
create index i_tipos_movilidad ON LOS_DEBATIENTES.BI_tipos_movilidad (tmo_descripcion)
create index i_rangos_etarios ON LOS_DEBATIENTES.BI_rangos_etarios (ret_inicio, ret_fin)
create index i_estados_pedidos ON LOS_DEBATIENTES.BI_estados_pedidos (epe_descripcion)
create index i_estados_reclamos ON LOS_DEBATIENTES.BI_estados_reclamos (ere_descripcion)
create index i_rangos_horarios ON LOS_DEBATIENTES.BI_rangos_horarios (rho_inicio, rho_fin)
create index i_dias ON LOS_DEBATIENTES.BI_dias (dia_descripcion)
create index i_periodos ON LOS_DEBATIENTES.BI_periodos (per_anio, per_mes)
create index i_tipos_reclamos ON LOS_DEBATIENTES.BI_tipos_reclamo (tre_descripcion)
create index i_pedidos_periodo ON LOS_DEBATIENTES.BI_pedidos (p_periodo)
create index i_pedidos_localidad ON LOS_DEBATIENTES.BI_pedidos (p_localidad)
create index i_pedidos_local ON LOS_DEBATIENTES.BI_pedidos (p_tipo_local, p_local)
create index i_pedidos_dia ON LOS_DEBATIENTES.BI_pedidos (p_dia)
create index i_mensajerias_periodo ON LOS_DEBATIENTES.BI_mensajerias (m_periodo)
create index i_mensajerias_localidad ON LOS_DEBATIENTES.BI_mensajerias (m_localidad)
create index i_mensajerias_dia ON LOS_DEBATIENTES.BI_mensajerias (m_dia)
create index i_reclamos_periodo ON LOS_DEBATIENTES.BI_reclamos (r_periodo)
create index i_reclamos_localidad ON LOS_DEBATIENTES.BI_reclamos (r_tipo_reclamo)
create index i_reclamos_local ON LOS_DEBATIENTES.BI_reclamos (r_local)
create index i_reclamos_dia ON LOS_DEBATIENTES.BI_reclamos (r_dia)

-- CREACION DE FUNCIONES

-- funcion para calcular edad en base a fecha de nacimiento
GO
create function LOS_DEBATIENTES.calcularEdad(@fecha date)
returns int
as
BEGIN
	declare @nuevoValor int
	set @nuevoValor = (SELECT DATEDIFF(YEAR, @fecha, GETDATE()) - 
        CASE
            WHEN DATEADD(YEAR, DATEDIFF(YEAR, @fecha, GETDATE()), @fecha) > GETDATE()
            THEN 1
            ELSE 0
        END)
        return @nuevoValor
END
GO

-- CREACION DE PROCEDURES PARA MIGRACION DE DATOS DE MODELO TRANSACCIONAL
-- CADA PROCEDURE MIGRA UNA TABLA EN ESPECIFICO

-- LOS_DEBATIENTES.BI_periodos
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_periodos
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.BI_periodos 
		select distinct  year(rec_fecha) per_anio, month(rec_fecha) per_mes from LOS_DEBATIENTES.reclamos
		union
		select  year(msj_fecha) per_anio, month(msj_fecha) per_mes from LOS_DEBATIENTES.mensajerias
		union
		select  year(ped_fecha) per_anio, month(ped_fecha) per_mes from LOS_DEBATIENTES.pedidos
END
GO

-- LOS_DEBATIENTES.BI_dias
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_dias
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.BI_dias 
		values ('Lunes', 1), ('Martes', 2), ('Miercoles', 3), ('Jueves', 4), ('Viernes', 5), ('Sabado', 6), ('Domingo', 7)
END
GO

-- LOS_DEBATIENTES.BI_rangos_horarios
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_rangos_horarios
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_rangos_horarios values (8, 9), (10, 11), (12, 13), (14, 15), (16, 17), (18, 19), (20, 21), (22, 23)
END
GO

-- LOS_DEBATIENTES.BI_localidades
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_localidades
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_localidades 
	select distinct lcd_descripcion loc_localidad, dim_provincia loc_provincia from LOS_DEBATIENTES.direcciones_mensajerias
	inner join LOS_DEBATIENTES.localidades on dim_localidad = lcd_id
	union 
	select lcd_descripcion loc_localidad, diu_provincia loc_provincia from LOS_DEBATIENTES.direcciones_usuarios
	inner join LOS_DEBATIENTES.localidades on diu_localidad = lcd_id
	union 
	select lcd_descripcion loc_localidad, dil_provincia loc_provincia from LOS_DEBATIENTES.direcciones_locales
	inner join LOS_DEBATIENTES.localidades on dil_localidad = lcd_id
END
GO

-- LOS_DEBATIENTES.BI_rangos_etarios
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_rangos_etarios
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_rangos_etarios values (0, 24), (25, 34), (35, 55), (56, 300)
	
END
GO

-- LOS_DEBATIENTES.BI_tipos_pago
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_tipos_pago
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_tipos_pago 
		select tdp_descripcion from LOS_DEBATIENTES.tipos_de_pago
END
GO

-- LOS_DEBATIENTES.BI_locales
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_locales
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_locales 
		select loc_nombre lok_nombre, loc_descripcion lok_descripcion, dil_direccion lok_direccion from LOS_DEBATIENTES.locales
		inner join LOS_DEBATIENTES.direcciones_locales on dil_id=loc_direccion
END
GO

-- LOS_DEBATIENTES.BI_tipos_local
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_tipos_local
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_tipos_local 
		select tlc_nombre tlo_descripcion from LOS_DEBATIENTES.tipos_de_local
END
GO

-- LOS_DEBATIENTES.BI_tipos_movilidad
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_tipos_movilidad
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_tipos_movilidad 
		select tdm_descripcion tmo_descripcion from LOS_DEBATIENTES.tipos_de_movilidad
END
GO

-- LOS_DEBATIENTES.BI_tipos_paquete
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_tipos_paquete
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_tipos_paquete 
		select paq_tipo tpa_tipo from LOS_DEBATIENTES.tipos_de_paquete
END
GO

-- LOS_DEBATIENTES.BI_estados_pedidos
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_estados_pedidos
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_estados_pedidos 
		select ep_descripcion epe_descripcion from LOS_DEBATIENTES.estados_pedido
END
GO

-- LOS_DEBATIENTES.BI_estados_envios_mensajeria
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_estados_envios_mensajeria
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_estados_envios_mensajeria 
		select edm_descripcion eem_descripcion from LOS_DEBATIENTES.estados_mensajeria
END
GO

-- LOS_DEBATIENTES.BI_estados_reclamos
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_estados_reclamos
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_estados_reclamos 
		select er_descripcion ere_descripcion from LOS_DEBATIENTES.estados_reclamo
END
GO

-- LOS_DEBATIENTES.BI_tipos_reclamo
GO
CREATE PROCEDURE LOS_DEBATIENTES.migracion_BI_tipos_reclamo
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_tipos_reclamo
		select tdr_descripcion tre_descripcion from LOS_DEBATIENTES.tipos_de_reclamo
END
GO

Create PROCEDURE LOS_DEBATIENTES.migracion_BI_pedidos
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_pedidos select
		per_id p_periodo,
		dia_id p_dia,
		rho_id p_rango_horario,
		lcd.loc_id p_localidad,
		re_usu.ret_id p_rango_etario_usuario,
		re_rep.ret_id p_rango_etario_repartidor,
		tpg_id p_tipo_pago,
		lok_id p_local,
		tlo_id p_tipo_local,
		tmo_id p_tipo_movilidad,
		epe_id p_estado_pedido,
		COUNT(distinct ped_id) p_cantidad_pedidos,
		SUM(env_precio) p_precio_envio,
		SUM(iif(epe_descripcion = 'Estado Mensajeria Cancelado', ped_total_servicio, 0)) p_montos_no_cobrados,
		SUM(DATEDIFF(MINUTE, ped_fecha , ped_fecha_entrega) - ped_tiempo_estimado_entrega) p_tiempo_de_entregas,
		SUM(ISNULL(ped_total_cupones, 0)) p_monto_cupones,
		SUM(ped_calificacion) p_calificaciones
	from LOS_DEBATIENTES.pedidos
		INNER JOIN LOS_DEBATIENTES.BI_periodos ON (year(ped_fecha) = per_anio and month(ped_fecha) = per_mes)
		INNER JOIN LOS_DEBATIENTES.BI_dias ON ((DATEPART(WEEKDAY, ped_fecha) + @@DATEFIRST - 2) % 7 + 1 = dia_numero)
		INNER JOIN LOS_DEBATIENTES.BI_rangos_horarios ON (DATEPART(HOUR, ped_fecha) BETWEEN rho_inicio AND rho_fin)
		INNER JOIN LOS_DEBATIENTES.envios ON env_pedido = ped_id
		INNER JOIN LOS_DEBATIENTES.repartidores ON (env_repartidor = rep_id)
		INNER JOIN LOS_DEBATIENTES.direcciones_usuarios ON env_direccion = diu_id
		INNER JOIN LOS_DEBATIENTES.localidades  ON diu_localidad = lcd_id
		INNER JOIN LOS_DEBATIENTES.BI_localidades lcd ON (lcd_descripcion = lcd.loc_localidad and lcd.loc_provincia = diu_provincia)
		INNER JOIN LOS_DEBATIENTES.usuarios ON (ped_usuario = usu_id)
		INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios re_usu ON (LOS_DEBATIENTES.calcularEdad(usu_fecha_nacimiento) BETWEEN re_usu.ret_inicio AND re_usu.ret_fin)
		INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios re_rep ON (LOS_DEBATIENTES.calcularEdad(rep_fecha_nacimiento) BETWEEN re_rep.ret_inicio AND re_rep.ret_fin)
		INNER JOIN LOS_DEBATIENTES.medios_de_pago ON (mdp_id = ped_medio_pago)
		INNER JOIN LOS_DEBATIENTES.tipos_de_pago ON (mdp_tipo = tdp_id)
		INNER JOIN LOS_DEBATIENTES.BI_tipos_pago ON (tpg_descripcion = tdp_descripcion)
		INNER JOIN LOS_DEBATIENTES.locales loca ON (ped_local = loca.loc_id)
		INNER JOIN LOS_DEBATIENTES.BI_locales ON (lok_descripcion = loca.loc_descripcion)
		INNER JOIN LOS_DEBATIENTES.tipos_de_local ON (loca.loc_tipo = tlc_id)
		INNER JOIN LOS_DEBATIENTES.BI_tipos_local ON (tlo_descripcion = tlc_nombre)
		INNER JOIN LOS_DEBATIENTES.tipos_de_movilidad ON (tdm_id = rep_tipo_movilidad)
		INNER JOIN LOS_DEBATIENTES.BI_tipos_movilidad ON (tdm_descripcion = tmo_descripcion)
		INNER JOIN LOS_DEBATIENTES.estados_pedido ON (ep_id = ped_estado)
		INNER JOIN LOS_DEBATIENTES.BI_estados_pedidos ON (ep_descripcion = epe_descripcion)
	group by 
		per_id, dia_id, rho_id, lcd.loc_id, re_usu.ret_id, re_rep.ret_id, tpg_id, lok_id, tlo_id, tmo_id, epe_id
END
GO

Create PROCEDURE LOS_DEBATIENTES.migracion_BI_mensajerias
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_mensajerias select
		per_id m_periodo,
		dia_id m_dia,
		rho_id m_rango_horario,
		loc_id m_localidad,
		re_usu.ret_id m_rango_etario_usuario ,
		re_rep.ret_id m_rango_etario_repartidor,
		tpg_id m_tipo_pago,
		tmo_id m_tipo_movilidad ,
		tpa_id m_tipo_paquete ,
		eem_id m_estado_mensajeria,
		SUM(msj_valor_asegurado) m_valores_asegurados,
		SUM(DATEDIFF(MINUTE, msj_fecha , msj_fecha_entrega) - msj_tiempo_estimado) m_tiempo_de_entregas,
		COUNT(distinct msj_id) m_cantidad_envios
	from LOS_DEBATIENTES.mensajerias
		INNER JOIN LOS_DEBATIENTES.BI_periodos ON (year(msj_fecha) = per_anio and month(msj_fecha) = per_mes)
		INNER JOIN LOS_DEBATIENTES.BI_dias ON ((DATEPART(WEEKDAY, msj_fecha) + @@DATEFIRST - 2) % 7 + 1 = dia_numero)
		INNER JOIN LOS_DEBATIENTES.BI_rangos_horarios ON (DATEPART(HOUR, msj_fecha) BETWEEN  rho_inicio AND rho_fin)
		INNER JOIN LOS_DEBATIENTES.direcciones_mensajerias ON msj_direccion = dim_id
		INNER JOIN LOS_DEBATIENTES.localidades ON dim_localidad = lcd_id
		INNER JOIN LOS_DEBATIENTES.BI_localidades ON (lcd_descripcion = loc_localidad and loc_provincia = dim_provincia)
		INNER JOIN LOS_DEBATIENTES.usuarios ON (msj_usuario = usu_id)
		INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios re_usu ON (LOS_DEBATIENTES.calcularEdad(usu_fecha_nacimiento) BETWEEN re_usu.ret_inicio AND re_usu.ret_fin)
		INNER JOIN LOS_DEBATIENTES.repartidores ON (msj_repartidor = rep_id)
		INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios re_rep ON (LOS_DEBATIENTES.calcularEdad(rep_fecha_nacimiento) BETWEEN re_rep.ret_inicio AND re_rep.ret_fin)
		INNER JOIN LOS_DEBATIENTES.medios_de_pago ON (mdp_id = msj_medio_de_pago)
		INNER JOIN LOS_DEBATIENTES.tipos_de_pago ON (mdp_tipo = tdp_id)
		INNER JOIN LOS_DEBATIENTES.BI_tipos_pago ON (tpg_descripcion = tdp_descripcion)
		INNER JOIN LOS_DEBATIENTES.tipos_de_movilidad ON (tdm_id = rep_tipo_movilidad)
		INNER JOIN LOS_DEBATIENTES.BI_tipos_movilidad ON (tdm_descripcion = tmo_descripcion)
		INNER JOIN LOS_DEBATIENTES.tipos_de_paquete ON (paq_id = msj_tipo_de_paquete)
		INNER JOIN LOS_DEBATIENTES.BI_tipos_paquete ON (tpa_tipo = paq_tipo)
		INNER JOIN LOS_DEBATIENTES.estados_mensajeria ON (edm_id = msj_estado)
		INNER JOIN LOS_DEBATIENTES.BI_estados_envios_mensajeria ON (edm_descripcion = eem_descripcion)
	group by 
		per_id, dia_id, rho_id, loc_id, re_usu.ret_id, re_rep.ret_id, tpg_id, tmo_id, tpa_id, eem_id
END
GO

Create PROCEDURE LOS_DEBATIENTES.migracion_BI_reclamos
AS
BEGIN
	SET NOCOUNT ON;
	insert into LOS_DEBATIENTES.BI_reclamos select 
		per_id r_periodo,
		dia_id r_dia,
		rho_id r_rango_horario,
		re_ope.ret_id r_rango_etario_operario,
		rec_local r_local,
		ere_id r_estado_reclamo,
		tre_id r_tipo_reclamo,
		COUNT(distinct rec_id) r_cantidad_reclamos,
		SUM(DATEDIFF(MINUTE, rec_fecha, rec_fecha_solucion)) r_tiempos_de_resolucion,
		SUM(rec_calificacion) r_calificaciones,
		SUM(ISNULL(cup_monto, 0)) r_monto_cupones
	from LOS_DEBATIENTES.reclamos
		INNER JOIN LOS_DEBATIENTES.BI_periodos ON (year(rec_fecha) = per_anio and month(rec_fecha) = per_mes)
		INNER JOIN LOS_DEBATIENTES.BI_dias ON ((DATEPART(WEEKDAY, rec_fecha) + @@DATEFIRST - 2) % 7 + 1 = dia_numero)
		INNER JOIN LOS_DEBATIENTES.BI_rangos_horarios ON (DATEPART(HOUR, rec_fecha) BETWEEN  rho_inicio AND rho_fin)
		INNER JOIN LOS_DEBATIENTES.operadores ON (rec_operador = op_id)
		INNER JOIN LOS_DEBATIENTES.usuarios ON (rec_usuario = usu_id)
		INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios re_usu ON (LOS_DEBATIENTES.calcularEdad(usu_fecha_nacimiento) BETWEEN re_usu.ret_inicio AND re_usu.ret_fin)
		INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios re_ope ON (LOS_DEBATIENTES.calcularEdad(op_fecha_nacimiento) BETWEEN re_ope.ret_inicio AND re_ope.ret_fin)
		INNER JOIN LOS_DEBATIENTES.estados_reclamo ON (er_id = rec_estado)
		INNER JOIN LOS_DEBATIENTES.BI_estados_reclamos ON (er_descripcion = ere_descripcion)
		INNER JOIN LOS_DEBATIENTES.tipos_de_reclamo ON (tdr_id = rec_tipo)
		INNER JOIN LOS_DEBATIENTES.BI_tipos_reclamo ON (tdr_descripcion = tre_descripcion)
		LEFT JOIN LOS_DEBATIENTES.reclamos_por_cupones ON (rxc_reclamo = rec_id)
		LEFT JOIN LOS_DEBATIENTES.cupones ON (rxc_cupon = cup_id)
	group by 
		per_id, dia_id, rho_id, re_ope.ret_id, rec_local, ere_id, tre_id
END											   
GO

-- EJECUCION DE PROCEDURES CREADOS

EXEC LOS_DEBATIENTES.migracion_BI_periodos
EXEC LOS_DEBATIENTES.migracion_BI_dias
EXEC LOS_DEBATIENTES.migracion_BI_rangos_horarios
EXEC LOS_DEBATIENTES.migracion_BI_localidades
EXEC LOS_DEBATIENTES.migracion_BI_rangos_etarios
EXEC LOS_DEBATIENTES.migracion_BI_tipos_pago
EXEC LOS_DEBATIENTES.migracion_BI_locales
EXEC LOS_DEBATIENTES.migracion_BI_tipos_local
EXEC LOS_DEBATIENTES.migracion_BI_tipos_movilidad
EXEC LOS_DEBATIENTES.migracion_BI_tipos_paquete
EXEC LOS_DEBATIENTES.migracion_BI_estados_pedidos
EXEC LOS_DEBATIENTES.migracion_BI_estados_envios_mensajeria
EXEC LOS_DEBATIENTES.migracion_BI_estados_reclamos
EXEC LOS_DEBATIENTES.migracion_BI_tipos_reclamo
EXEC LOS_DEBATIENTES.migracion_BI_pedidos
EXEC LOS_DEBATIENTES.migracion_BI_mensajerias
EXEC LOS_DEBATIENTES.migracion_BI_reclamos

-- CREACION DE VISTAS
GO
create view LOS_DEBATIENTES.MejorDiaYHorarioPedidos AS
select 
	loc_localidad, per_anio, per_mes, tlo_descripcion, CONCAT(dia_descripcion, ' ', rho_inicio, ' - ', rho_fin) dia_semanal
from LOS_DEBATIENTES.BI_pedidos
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON  per_id = p_periodo
	INNER JOIN LOS_DEBATIENTES.BI_localidades ON loc_id = p_localidad
	INNER JOIN LOS_DEBATIENTES.BI_tipos_local ON tlo_id = p_tipo_local
	INNER JOIN LOS_DEBATIENTES.BI_dias ON dia_id = p_dia
	INNER JOIN LOS_DEBATIENTES.BI_rangos_horarios ON rho_id = p_rango_horario 
where p_estado_pedido is not null
group by loc_id, per_id, tlo_id, p_dia, p_rango_horario, per_anio, per_mes, loc_localidad, 
	tlo_descripcion, dia_descripcion, rho_inicio, rho_fin
having CONCAT(p_dia, p_rango_horario) = (
	select top 1 CONCAT(p_dia, p_rango_horario)
	from LOS_DEBATIENTES.BI_pedidos 
	where loc_id = p_localidad and per_id = p_periodo and tlo_id = p_tipo_local
	group by p_localidad, p_periodo, p_tipo_local, p_dia, p_rango_horario
	order by sum(p_cantidad_pedidos) desc
)

GO
create view LOS_DEBATIENTES.MontoCanceladosLocales AS
select 
	lok_nombre, CONCAT(dia_descripcion, ' ', rho_inicio, ' - ', rho_fin) dia_semanal, sum(p_montos_no_cobrados) monto_total
from LOS_DEBATIENTES.BI_pedidos
	INNER JOIN LOS_DEBATIENTES.BI_dias ON dia_id = p_dia
	INNER JOIN LOS_DEBATIENTES.BI_rangos_horarios ON rho_id = p_rango_horario 
	INNER JOIN LOS_DEBATIENTES.BI_locales ON lok_id = p_local
	INNER JOIN LOS_DEBATIENTES.BI_estados_pedidos ON epe_id = p_estado_pedido
group by p_local, p_dia, p_rango_horario, lok_nombre, dia_descripcion, rho_inicio, rho_fin

GO
create view LOS_DEBATIENTES.PromedioMensualEnviosLocalidad AS
select 
	loc_localidad, per_anio, per_mes, sum(p_precio_envios) / sum(p_cantidad_pedidos) promedio
from LOS_DEBATIENTES.BI_pedidos
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON per_id = p_periodo
	INNER JOIN LOS_DEBATIENTES.BI_localidades ON loc_id = p_localidad
group by p_localidad, p_periodo, loc_localidad, per_anio, per_mes

GO
create view LOS_DEBATIENTES.PromedioDiaSemanalDesvioMovilidad AS
select 
	'pedido' hecho, tmo_descripcion, CONCAT(dia_descripcion, ' ', rho_inicio, ' - ', rho_fin) dia_semanal, 
	sum(p_tiempo_de_entregas) / sum(p_cantidad_pedidos) promedio_desvio
from LOS_DEBATIENTES.BI_pedidos
	INNER JOIN LOS_DEBATIENTES.BI_dias ON dia_id = p_dia
	INNER JOIN LOS_DEBATIENTES.BI_rangos_horarios ON rho_id = p_rango_horario 
	INNER JOIN LOS_DEBATIENTES.BI_tipos_movilidad ON tmo_id = p_tipo_movilidad
group by p_tipo_movilidad, p_dia, p_rango_horario, tmo_descripcion, dia_descripcion, rho_inicio, rho_fin
union
select 
	'mensajeria' hecho, tmo_descripcion, CONCAT(dia_descripcion, ' ', rho_inicio, ' - ', rho_fin) dia_semanal, 
	sum(m_tiempo_de_entregas) / sum(m_cantidad_envios) promedio_desvio
from LOS_DEBATIENTES.BI_mensajerias
	INNER JOIN LOS_DEBATIENTES.BI_dias ON dia_id = m_dia
	INNER JOIN LOS_DEBATIENTES.BI_rangos_horarios ON rho_id = m_rango_horario 
	INNER JOIN LOS_DEBATIENTES.BI_tipos_movilidad ON tmo_id = m_tipo_movilidad
group by m_tipo_movilidad, m_dia, m_rango_horario, tmo_descripcion, dia_descripcion, rho_inicio, rho_fin

GO
create view LOS_DEBATIENTES.MontoCuponesPorMesYRangoEtario AS
select 
	CONCAT(ret_inicio, ' - ', ret_fin) rango_etario, per_anio, per_mes, sum(p_monto_cupones) monto_cupones
from LOS_DEBATIENTES.BI_pedidos
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON per_id = p_periodo
	INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios ON ret_id = p_rango_etario_usuario
group by p_rango_etario_usuario, p_periodo, ret_inicio, ret_fin, per_anio, per_mes

GO
create view LOS_DEBATIENTES.CalificacionMensualPorLocal AS
select 
	lok_nombre, per_anio, per_mes, sum(p_calificaciones) / sum(p_cantidad_pedidos) promedio_calificacion
from LOS_DEBATIENTES.BI_pedidos
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON per_id = p_periodo
	INNER JOIN LOS_DEBATIENTES.BI_locales ON lok_id = p_local
group by lok_id, p_periodo, lok_nombre, per_anio, per_mes

GO
create view LOS_DEBATIENTES.PorcentajePedidosMensajeriasEntregadas AS
select 
	'pedido' hecho, loc_localidad, per_anio, per_mes, CONCAT(ret_inicio, ' - ', ret_fin) rango_etario,
	CAST(SUM(p_cantidad_pedidos) * 100 AS DECIMAL(10,2)) / (
		select SUM(p_cantidad_pedidos) from LOS_DEBATIENTES.BI_pedidos 
		where p_periodo = per_id
	) porcentaje_del_mes
from LOS_DEBATIENTES.BI_pedidos
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON per_id = p_periodo
	INNER JOIN LOS_DEBATIENTES.BI_localidades ON loc_id = p_localidad
	INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios ON ret_id = p_rango_etario_repartidor
	INNER JOIN LOS_DEBATIENTES.BI_estados_pedidos ON epe_id = p_estado_pedido
where epe_descripcion = 'Estado Mensajeria Entregado'
group by loc_id, per_id, loc_localidad, per_anio, per_mes, ret_inicio, ret_fin
union
select 
	'mensajeria' hecho, loc_localidad, per_anio, per_mes, CONCAT(ret_inicio, ' - ', ret_fin) rango_etario,
	CAST(SUM(m_cantidad_envios) * 100 AS DECIMAL(10,2)) / (
		select SUM(m_cantidad_envios) from LOS_DEBATIENTES.BI_mensajerias 
		where m_periodo = per_id
	) porcentaje_del_mes
from LOS_DEBATIENTES.BI_mensajerias
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON per_id = m_periodo
	INNER JOIN LOS_DEBATIENTES.BI_localidades ON loc_id = m_localidad
	INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios ON ret_id = m_rango_etario_repartidor
	INNER JOIN LOS_DEBATIENTES.BI_estados_envios_mensajeria ON eem_id = m_estado_mensajeria
where eem_descripcion = 'Estado Mensajeria Entregado'
group by loc_id, per_id, loc_localidad, per_anio, per_mes, ret_inicio, ret_fin

GO
create view LOS_DEBATIENTES.PromedioValorAseguradoTipoPaquete AS
select 
	tpa_tipo, per_anio, per_mes, SUM(m_valores_asegurados) / SUM(m_cantidad_envios) promedio_valor_asegurado
from LOS_DEBATIENTES.BI_mensajerias
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON per_id = m_periodo
	INNER JOIN LOS_DEBATIENTES.BI_tipos_paquete ON tpa_id = m_tipo_paquete
group by tpa_id, per_id, tpa_tipo, per_anio, per_mes


GO
create view LOS_DEBATIENTES.ReclamosMensualesPorLocalYDiaSemanal AS
select 
	lok_nombre, per_anio, per_mes, CONCAT(dia_descripcion, ' ', rho_inicio, ' - ', rho_fin) dia_semanal, SUM(r_cantidad_reclamos) cantidad_reclamos
from LOS_DEBATIENTES.BI_reclamos
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON per_id = r_periodo
	INNER JOIN LOS_DEBATIENTES.BI_locales ON lok_id = r_local
	INNER JOIN LOS_DEBATIENTES.BI_dias ON dia_id = r_dia
	INNER JOIN LOS_DEBATIENTES.BI_rangos_horarios ON rho_id = r_rango_horario
group by lok_id, per_id, dia_id, rho_id, per_anio, per_mes, lok_nombre, dia_descripcion, rho_inicio, rho_fin

GO
create view LOS_DEBATIENTES.PromedioResolucionReclamos AS
select 
	tre_descripcion, per_anio, per_mes, CONCAT(ret_inicio, ' - ', ret_fin) rango_etario,
	SUM(r_tiempos_de_resolucion) / SUM(r_cantidad_reclamos) promedio_resolucion
from LOS_DEBATIENTES.BI_reclamos
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON per_id = r_periodo
	INNER JOIN LOS_DEBATIENTES.BI_rangos_etarios ON ret_id = r_rango_etario_operario
	INNER JOIN LOS_DEBATIENTES.BI_tipos_reclamo ON tre_id = r_tipo_reclamo
group by tre_id, per_id, ret_id, tre_descripcion, per_anio, per_mes, ret_inicio, ret_fin

GO
create view LOS_DEBATIENTES.MontoCuponesDeReclamos AS
select 
	per_anio, per_mes, SUM(r_montos_cupones) monto_cupones_generados
from LOS_DEBATIENTES.BI_reclamos
	INNER JOIN LOS_DEBATIENTES.BI_periodos ON per_id = r_periodo
group by per_id, per_anio, per_mes