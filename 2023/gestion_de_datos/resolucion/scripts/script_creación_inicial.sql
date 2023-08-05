-- CREACION DE ESQUEMA

create SCHEMA LOS_DEBATIENTES
GO

-- CREACION DE TABLAS
create table LOS_DEBATIENTES.usuarios (
	usu_id decimal(18, 0) not null identity(1,1),
	usu_nombre varchar(255) not null,
	usu_apellido varchar(255) not null,
	usu_dni decimal(18, 0) not null,
	usu_fecha_registro datetime2(3) not null,
	usu_telefono decimal(18, 0) not null,
	usu_mail nvarchar(255) not null,
	usu_fecha_nacimiento date not null
)

create table LOS_DEBATIENTES.localidades (
	lcd_id decimal(18, 0) not null identity(1,1),
	lcd_descripcion nvarchar(255) not null
)

create table LOS_DEBATIENTES.tipos_de_reclamo (
	tdr_id decimal(18, 0) not null identity(1,1),
	tdr_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.tipos_de_movilidad (
	tdm_id decimal(18, 0) not null identity(1,1),
	tdm_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.estados_reclamo (
	er_id decimal(18, 0) not null identity(1,1),
	er_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.estados_mensajeria (
	edm_id decimal(18, 0) not null identity(1,1),
	edm_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.tipos_de_pago (
	tdp_id decimal(18, 0) not null identity(1,1),
	tdp_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.dias (
	dia_id decimal(18, 0) not null identity(1,1),
	dia_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.categorias (
	cat_id decimal(18, 0) not null identity(1,1),
	cat_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.tipos_de_local (
	tlc_id decimal(18, 0) not null identity(1,1),
	tlc_nombre nvarchar(50) not null,
)

create table LOS_DEBATIENTES.tipo_por_categoria (
	txc_id decimal(18, 0) not null identity(1,1),
	txc_tipo_local decimal(18, 0) not null,  -- AGREGAR FK tipo_local
	txc_categoria decimal(18, 0) not null, -- AGREGAR FK LOS_DEBATIENTES.categorias
)

create table LOS_DEBATIENTES.horarios (
	hor_id decimal(18, 0) not null identity(1,1),
	hor_hora_apertura decimal(18, 0) not null,
	hor_hora_cierre decimal(18, 0) not null,
	hor_dia decimal(18, 0) not null, --AGREGAR FK dia
	hor_local decimal(18, 0) not null --AGREGAR FK LOS_DEBATIENTES.locales
)

create table LOS_DEBATIENTES.locales (
	loc_id decimal(18, 0) not null identity(1,1),
	loc_nombre nvarchar(100) not null,
	loc_descripcion nvarchar(255) not null,
	loc_direccion decimal(18,0) not null, --AGREGAR FK direcciones
	loc_tipo decimal(18, 0) not null, -- AGREGAR FK LOS_DEBATIENTES.tipos_de_local
)

create table LOS_DEBATIENTES.direcciones_locales (
	dil_id decimal(18, 0) not null identity(1,1),
	dil_direccion nvarchar(255) not null,
	dil_localidad decimal(18,0) not null, --AGREGAR FK LOS_DEBATIENTES.localidades
	dil_provincia nvarchar(255) not null
)

create table LOS_DEBATIENTES.direcciones_usuarios (
	diu_id decimal(18, 0) not null identity(1,1),
	diu_direccion nvarchar(255) not null,
	diu_localidad decimal(18,0) not null, --AGREGAR FK LOS_DEBATIENTES.localidades
	diu_provincia nvarchar(255) not null,
	diu_usuario decimal(18, 0) not null, -- AGREGAR FK LOS_DEBATIENTES.usuarios
	diu_nombre nvarchar(50) not null
)

create table LOS_DEBATIENTES.direcciones_operadores (
	dio_id decimal(18, 0) not null identity(1,1),
	dio_descripcion nvarchar(255) not null
)

create table LOS_DEBATIENTES.direcciones_mensajerias (
	dim_id decimal(18, 0) not null identity(1,1),
	dim_dir_origen nvarchar(255) not null,
	dim_dir_destino nvarchar(255) not null,
	dim_localidad decimal(18,0) not null, --AGREGAR FK LOS_DEBATIENTES.localidades
	dim_provincia nvarchar(255) not null,
)

create table LOS_DEBATIENTES.repartidores (
	rep_id decimal(18, 0) not null identity(1,1),
	rep_nombre nvarchar(255) not null,
	rep_apellido nvarchar(255) not null,
	rep_dni decimal(18, 0) not null,
	rep_telefono decimal(18, 0) not null,
	rep_direccion nvarchar(255) not null,
	rep_email nvarchar(255) not null,
	rep_fecha_nacimiento date not null,
	rep_tipo_movilidad decimal(18, 0) not null  -- AGREGAR FK LOS_DEBATIENTES.tipos_de_movilidad
)

create table LOS_DEBATIENTES.zona_de_trabajo (
	zdt_id decimal(18, 0) not null identity(1,1),
	zdt_localidad decimal(18, 0) not null,  -- AGREGAR FK localidad
	zdt_repartidor decimal(18, 0) not null, -- AGREGAR FK repartidor
	zdt_activo bit
)

create table LOS_DEBATIENTES.estados_pedido (
	ep_id decimal(18, 0) not null identity(1,1),
	ep_descripcion nvarchar(50) not null
)

create table LOS_DEBATIENTES.envios (
	env_id decimal(18, 0) not null identity(1,1),
	env_direccion decimal(18, 0) not null, -- AGREGAR FK direcciones
	env_precio decimal(18, 2) not null,
	env_propina decimal(18, 2) not null,
	env_repartidor decimal(18, 0),  -- AGREGAR FK LOS_DEBATIENTES.repartidores
	env_pedido decimal(18, 0)  -- AGREGAR FK LOS_DEBATIENTES.pedidos
)

create table LOS_DEBATIENTES.medios_de_pago (
	mdp_id decimal(18, 0) not null identity(1,1),
	mdp_nro_tarjeta nvarchar(50),
	mdp_tipo decimal(18, 0) not null, -- AGREGAR FK LOS_DEBATIENTES.tipos_de_pago
	mdp_marca_tarjeta nvarchar(100),
	mdp_usuario decimal(18, 0) not null-- AGREGAR FK LOS_DEBATIENTES.usuarios
)

create table LOS_DEBATIENTES.pedidos (
	ped_id decimal(18, 0) not null identity(1,1),
	ped_numero decimal(18, 0) not null,
	ped_usuario decimal(18, 0) not null, -- AGREGAR FK LOS_DEBATIENTES.usuarios
	ped_local decimal(18, 0) not null, -- AGREGAR FK LOS_DEBATIENTES.locales
	ped_tarifa_servicio decimal(18, 2) not null,
	ped_total_servicio decimal(18, 2) not null,
	ped_observaciones nvarchar(255) not null,
	ped_fecha datetime2(3) not null,
	ped_fecha_entrega datetime2(3) not null,
	ped_tiempo_estimado_entrega decimal(18, 2) not null,
	ped_calificacion decimal(18, 0),
	ped_estado decimal(18, 0) not null, --AGREGAR FK LOS_DEBATIENTES.estados_pedido
	ped_medio_pago decimal(18, 0) not null, -- AGREGAR FK medio de pago
	ped_total_cupones decimal(18, 2) not null,
	ped_total_productos decimal(18, 2) not null
)

create table LOS_DEBATIENTES.cupones_por_pedidos (
	cxp_id decimal(18, 0) not null identity(1,1),
	cxp_cupon decimal(18, 0) not null, --AGREGAR FK LOS_DEBATIENTES.cupones
	cxp_pedido decimal(18,0) not null --AGREGAR FK LOS_DEBATIENTES.pedidos
)

create table LOS_DEBATIENTES.productos (
	prd_id decimal(18, 0) not null identity(1,1),
	prd_codigo nvarchar(50) not null,
	prd_local decimal(18, 0) not null, --AGREGAR FK LOS_DEBATIENTES.locales
	prd_nombre nvarchar(50) not null,
	prd_descripcion nvarchar(255),
	prd_precio decimal(18, 2) not null
)

create table LOS_DEBATIENTES.productos_por_pedidos (
	pxp_id decimal(18, 0) not null identity(1,1),
	pxp_pedido decimal(18, 0) not null,  -- AGREGAR FK LOS_DEBATIENTES.pedidos
	pxp_producto decimal(18, 0) not null, -- AGREGAR FK LOS_DEBATIENTES.productos
	pxp_cantidad decimal(18, 0) not null,
	pxp_precio decimal(18, 2) not null
)

create table LOS_DEBATIENTES.cupones (
	cup_id decimal(18, 0) not null identity(1,1),
	cup_nro decimal(18,0) not null,
	cup_monto decimal(18, 0) not null,
	cup_fecha_alta datetime2(3) not null,
	cup_fecha_vencimiento datetime2(3) not null,
	cup_tipo decimal(18,0) not null -- AGREGAR FK LOS_DEBATIENTES.tipos_de_cupon
)

create table LOS_DEBATIENTES.mensajerias (
	msj_id decimal(18, 0) not null identity(1,1),
	msj_direccion decimal(18,0) not null, -- AGREGAR FK LOS_DEBATIENTES.direcciones_mensajerias
	msj_km decimal(18, 2) not null,
	msj_valor_asegurado decimal(18, 2) not null,
	msj_precio_env decimal(18, 2) not null,
	msj_precio_seguro decimal(18, 2) not null,
	msj_propina decimal(18, 2) not null,
	msj_total decimal(18, 2) not null,
	msj_observaciones nvarchar(255) not null,
	msj_fecha datetime2(3) not null,
	msj_fecha_entrega datetime2(3) not null,
	msj_tiempo_estimado decimal(18, 2) not null,
	msj_calificacion decimal(18, 0) not null,
	msj_usuario decimal(18, 0) not null, --AGREGAR FK LOS_DEBATIENTES.usuarios
	msj_tipo_de_paquete decimal(18, 0) not null, --AGREGAR FK paquetes
	msj_repartidor decimal(18, 0), --AGREGAR FK LOS_DEBATIENTES.repartidores
	msj_medio_de_pago decimal(18, 0) not null, --AGREGAR FK medios de pago
	msj_estado decimal(18, 0) not null --AGREGAR FK esatdos_mensajeria
)

create table LOS_DEBATIENTES.tipos_de_paquete (
	paq_id decimal(18, 0) not null identity(1,1),
	paq_tipo nvarchar(50) not null,
	paq_alto_max decimal(18, 2) not null,
	paq_ancho_max decimal(18, 2) not null,
	paq_largo_max decimal(18, 2) not null,
	paq_peso_max decimal(18, 2) not null,
	paq_precio decimal(18, 2) not null
)

create table LOS_DEBATIENTES.reclamos (
	rec_id decimal(18, 0) not null identity(1,1),
	rec_usuario decimal(18, 0) not null, --AGREGAR FK LOS_DEBATIENTES.usuarios
	rec_fecha datetime2(3) not null,
	rec_descripcion nvarchar(255) not null,
	rec_fecha_solucion datetime2(3) not null,
	rec_solucion nvarchar(255) not null,
	rec_calificacion decimal(18, 0),
	rec_tipo decimal(18, 0) not null, --AGREGAR FK LOS_DEBATIENTES.tipos_de_reclamo
	rec_estado decimal(18, 0) not null, --AGREGAR FK LOS_DEBATIENTES.estados_reclamo
	rec_pedido decimal(18, 0) not null, --AGREGAR FK LOS_DEBATIENTES.pedidos
	rec_operador decimal(18,0), --AGREGAR FK LOS_DEBATIENTES.operadores,
	rec_local decimal(18,0) not null, --AGREGAR FK LOS_DEBATIENTES.locales,
)

create table LOS_DEBATIENTES.reclamos_por_cupones (
	rxc_id decimal(18, 0) not null identity(1,1),
	rxc_reclamo decimal(18,0) not null, --AGREGAR FK LOS_DEBATIENTES.reclamos
	rxc_cupon decimal(18,0) not null, --AGREGAR FK LOS_DEBATIENTES.cupones
)

create table LOS_DEBATIENTES.operadores (
	op_id decimal(18,0) not null identity(1,1),
	op_nombre nvarchar(255) not null,
	op_apellido nvarchar(255) not null,
	op_dni decimal(18, 0) not null,
	op_telefono decimal(18, 0) not null,
	op_direccion decimal(18,0), --AGREGAR FK LOS_DEBATIENTES.direcciones_operadores
	op_mail nvarchar(255) not null,
	op_fecha_nacimiento date not null
)

create table LOS_DEBATIENTES.tipos_de_cupon (
	tdc_id decimal(18, 0) not null identity(1,1),
	tdc_descripcion nvarchar(50) not null,
)

--CREACION DE PRIMARY KEYS

alter table LOS_DEBATIENTES.usuarios add constraint pk_usuario primary key (usu_id)
alter table LOS_DEBATIENTES.tipos_de_local add constraint pk_tlc primary key (tlc_id)
alter table LOS_DEBATIENTES.tipos_de_cupon add constraint pk_tdc primary key (tdc_id)
alter table LOS_DEBATIENTES.horarios add constraint pk_hor primary key (hor_id) 
alter table LOS_DEBATIENTES.locales add constraint pk_loc primary key (loc_id) 
alter table LOS_DEBATIENTES.repartidores add constraint pk_rep primary key (rep_id)
alter table LOS_DEBATIENTES.envios add constraint pk_env primary key (env_id)
alter table LOS_DEBATIENTES.medios_de_pago add constraint pk_mdp primary key (mdp_id)
alter table LOS_DEBATIENTES.pedidos add constraint pk_ped primary key (ped_id)
alter table LOS_DEBATIENTES.cupones_por_pedidos add constraint pk_cxp primary key (cxp_id)
alter table LOS_DEBATIENTES.productos add constraint pk_prd primary key (prd_id)
alter table LOS_DEBATIENTES.productos_por_pedidos add constraint pk_pxp primary key (pxp_id)
alter table LOS_DEBATIENTES.cupones add constraint pk_cup primary key (cup_id)
alter table LOS_DEBATIENTES.mensajerias add constraint pk_msj primary key (msj_id)
alter table LOS_DEBATIENTES.direcciones_mensajerias add constraint pk_dim primary key (dim_id)
alter table LOS_DEBATIENTES.tipos_de_paquete add constraint pk_paq primary key (paq_id)
alter table LOS_DEBATIENTES.reclamos add constraint pk_rec primary key (rec_id)
alter table LOS_DEBATIENTES.reclamos_por_cupones add constraint pk_rec_cup primary key (rxc_id)
alter table LOS_DEBATIENTES.operadores add constraint pk_ope primary key (op_id)
alter table LOS_DEBATIENTES.direcciones_usuarios add constraint pk_diu primary key (diu_id)
alter table LOS_DEBATIENTES.direcciones_locales add constraint pk_dil primary key (dil_id)
alter table LOS_DEBATIENTES.direcciones_operadores add constraint pk_dio primary key (dio_id)
alter table LOS_DEBATIENTES.estados_pedido add constraint pk_ep primary key (ep_id)
alter table LOS_DEBATIENTES.dias add constraint pk_dia primary key (dia_id)
alter table LOS_DEBATIENTES.tipos_de_pago add constraint pk_tdp primary key (tdp_id)
alter table LOS_DEBATIENTES.estados_mensajeria add constraint pk_edm primary key (edm_id)
alter table LOS_DEBATIENTES.tipos_de_movilidad add constraint pk_tdm primary key (tdm_id)
alter table LOS_DEBATIENTES.tipos_de_reclamo add constraint pk_tdr primary key (tdr_id)
alter table LOS_DEBATIENTES.estados_reclamo add constraint pk_er primary key (er_id)
alter table LOS_DEBATIENTES.tipo_por_categoria add constraint pk_txc primary key (txc_id)
alter table LOS_DEBATIENTES.categorias add constraint pk_cat primary key (cat_id)
alter table LOS_DEBATIENTES.localidades add constraint pk_lcd primary key (lcd_id)
alter table LOS_DEBATIENTES.zona_de_trabajo add constraint pk_zdt primary key (zdt_id)

--CREACION DE FOREIGN KEYS

alter table LOS_DEBATIENTES.horarios add constraint fk_hor_loc foreign key (hor_local) references LOS_DEBATIENTES.locales (loc_id)
alter table LOS_DEBATIENTES.horarios add constraint fk_hor_dia foreign key (hor_dia) references LOS_DEBATIENTES.dias (dia_id)
alter table LOS_DEBATIENTES.locales add constraint fk_loc_tipo foreign key (loc_tipo) references LOS_DEBATIENTES.tipos_de_local (tlc_id)
alter table LOS_DEBATIENTES.locales add constraint fk_loc_direccion foreign key (loc_direccion) references LOS_DEBATIENTES.direcciones_locales (dil_id)
alter table LOS_DEBATIENTES.envios add constraint fk_env_direccion foreign key (env_direccion) references LOS_DEBATIENTES.direcciones_usuarios (diu_id)
alter table LOS_DEBATIENTES.envios add constraint fk_env_repartidor foreign key (env_repartidor) references LOS_DEBATIENTES.repartidores (rep_id)
alter table LOS_DEBATIENTES.envios add constraint fk_env_pedido foreign key (env_pedido) references LOS_DEBATIENTES.pedidos (ped_id)
alter table LOS_DEBATIENTES.medios_de_pago add constraint fk_mdp_usuario foreign key (mdp_usuario) references LOS_DEBATIENTES.usuarios (usu_id)
alter table LOS_DEBATIENTES.medios_de_pago add constraint fk_mdp_tipo foreign key (mdp_tipo) references LOS_DEBATIENTES.tipos_de_pago (tdp_id)
alter table LOS_DEBATIENTES.pedidos add constraint fk_ped_usuario foreign key (ped_usuario) references LOS_DEBATIENTES.usuarios (usu_id)
alter table LOS_DEBATIENTES.pedidos add constraint fk_ped_local foreign key (ped_local) references LOS_DEBATIENTES.locales (loc_id)
alter table LOS_DEBATIENTES.pedidos add constraint fk_ped_medio_pago foreign key (ped_medio_pago) references LOS_DEBATIENTES.medios_de_pago (mdp_id)
alter table LOS_DEBATIENTES.pedidos add constraint fk_ped_estado foreign key (ped_estado) references LOS_DEBATIENTES.estados_pedido (ep_id)
alter table LOS_DEBATIENTES.cupones_por_pedidos add constraint fk_cxp_cupon foreign key (cxp_cupon) references LOS_DEBATIENTES.cupones (cup_id)
alter table LOS_DEBATIENTES.cupones_por_pedidos add constraint fk_cxp_pedido foreign key (cxp_pedido) references LOS_DEBATIENTES.pedidos (ped_id)
alter table LOS_DEBATIENTES.productos add constraint fk_prd_local foreign key (prd_local) references LOS_DEBATIENTES.locales (loc_id)
alter table LOS_DEBATIENTES.productos_por_pedidos add constraint fk_pxp_pedido foreign key (pxp_pedido) references LOS_DEBATIENTES.pedidos (ped_id)
alter table LOS_DEBATIENTES.productos_por_pedidos add constraint fk_pxp_producto foreign key (pxp_producto) references LOS_DEBATIENTES.productos (prd_id)
alter table LOS_DEBATIENTES.direcciones_mensajerias add constraint fk_dim_localidad foreign key (dim_localidad) references LOS_DEBATIENTES.localidades (lcd_id)
alter table LOS_DEBATIENTES.mensajerias add constraint fk_msj_usuario foreign key (msj_usuario) references LOS_DEBATIENTES.usuarios (usu_id)
alter table LOS_DEBATIENTES.mensajerias add constraint fk_msj_tipo_de_paquete foreign key (msj_tipo_de_paquete) references LOS_DEBATIENTES.tipos_de_paquete (paq_id)
alter table LOS_DEBATIENTES.mensajerias add constraint fk_msj_repartidor foreign key (msj_repartidor) references LOS_DEBATIENTES.repartidores (rep_id)
alter table LOS_DEBATIENTES.mensajerias add constraint fk_msj_medio_de_pago foreign key (msj_medio_de_pago) references LOS_DEBATIENTES.medios_de_pago (mdp_id)
alter table LOS_DEBATIENTES.mensajerias add constraint fk_msj_estado foreign key (msj_estado) references LOS_DEBATIENTES.estados_mensajeria (edm_id)
alter table LOS_DEBATIENTES.mensajerias add constraint fk_msj_direccion foreign key (msj_direccion) references LOS_DEBATIENTES.direcciones_mensajerias (dim_id)
alter table LOS_DEBATIENTES.reclamos add constraint fk_rec_usuario foreign key (rec_usuario) references LOS_DEBATIENTES.usuarios (usu_id)
alter table LOS_DEBATIENTES.reclamos add constraint fk_rec_pedido foreign key (rec_pedido) references LOS_DEBATIENTES.pedidos (ped_id)
alter table LOS_DEBATIENTES.reclamos add constraint fk_rec_operador foreign key (rec_operador) references LOS_DEBATIENTES.operadores (op_id)
alter table LOS_DEBATIENTES.reclamos add constraint fk_rec_tipo foreign key (rec_tipo) references LOS_DEBATIENTES.tipos_de_reclamo (tdr_id)
alter table LOS_DEBATIENTES.reclamos add constraint fk_rec_estado foreign key (rec_estado) references LOS_DEBATIENTES.estados_reclamo (er_id)
alter table LOS_DEBATIENTES.reclamos add constraint fk_rec_local foreign key (rec_local) references LOS_DEBATIENTES.locales (loc_id)
alter table LOS_DEBATIENTES.reclamos_por_cupones add constraint fk_rxc_cupon foreign key (rxc_cupon) references LOS_DEBATIENTES.cupones (cup_id)
alter table LOS_DEBATIENTES.reclamos_por_cupones add constraint fk_rxc_reclamo foreign key (rxc_reclamo) references LOS_DEBATIENTES.reclamos (rec_id)
alter table LOS_DEBATIENTES.operadores add constraint fk_op_direccion foreign key (op_direccion) references LOS_DEBATIENTES.direcciones_operadores (dio_id)
alter table LOS_DEBATIENTES.direcciones_usuarios add constraint fk_diu_localidad foreign key (diu_localidad) references LOS_DEBATIENTES.localidades (lcd_id)
alter table LOS_DEBATIENTES.direcciones_usuarios add constraint fk_diu_usuario foreign key (diu_usuario) references LOS_DEBATIENTES.usuarios (usu_id)
alter table LOS_DEBATIENTES.direcciones_locales add constraint fk_dil_localidad foreign key (dil_localidad) references LOS_DEBATIENTES.localidades (lcd_id)
alter table LOS_DEBATIENTES.repartidores add constraint fk_rep_tipo_movilidad foreign key (rep_tipo_movilidad) references LOS_DEBATIENTES.tipos_de_movilidad (tdm_id)
alter table LOS_DEBATIENTES.tipo_por_categoria add constraint fk_txc_tipo_local foreign key (txc_tipo_local) references LOS_DEBATIENTES.tipos_de_local (tlc_id)
alter table LOS_DEBATIENTES.tipo_por_categoria add constraint fk_txc_categoria foreign key (txc_categoria) references LOS_DEBATIENTES.categorias (cat_id)
alter table LOS_DEBATIENTES.zona_de_trabajo add constraint fk_zdt_localidad foreign key (zdt_localidad) references LOS_DEBATIENTES.localidades (lcd_id)
alter table LOS_DEBATIENTES.zona_de_trabajo add constraint fk_zdt_repartidor foreign key (zdt_repartidor) references LOS_DEBATIENTES.repartidores (rep_id)
alter table LOS_DEBATIENTES.cupones add constraint fk_cup_tipo foreign key (cup_tipo) references LOS_DEBATIENTES.tipos_de_cupon (tdc_id)

--CREACION DE UNIQUES

alter table LOS_DEBATIENTES.usuarios add constraint uc_usu_dni unique (usu_dni)
alter table LOS_DEBATIENTES.usuarios add constraint uc_usu_telefono unique (usu_telefono)
alter table LOS_DEBATIENTES.pedidos add constraint uc_ped_numero unique (ped_numero)
alter table LOS_DEBATIENTES.locales add constraint uc_locales unique (loc_nombre, loc_direccion)
alter table LOS_DEBATIENTES.repartidores add constraint uc_rep_dni unique (rep_dni)
alter table LOS_DEBATIENTES.repartidores add constraint uc_rep_telefono unique (rep_telefono)
alter table LOS_DEBATIENTES.repartidores add constraint uc_rep_email unique (rep_email)
alter table LOS_DEBATIENTES.medios_de_pago add constraint uc_mdp unique (mdp_tipo, mdp_nro_tarjeta, mdp_marca_tarjeta, mdp_usuario)
alter table LOS_DEBATIENTES.productos add constraint uc_prd unique (prd_codigo, prd_local)
alter table LOS_DEBATIENTES.productos_por_pedidos add constraint uc_pxp unique (pxp_pedido, pxp_producto)
alter table LOS_DEBATIENTES.operadores add constraint uc_op_dni_tel unique (op_dni, op_telefono)
alter table LOS_DEBATIENTES.cupones add constraint uc_cup_nro unique (cup_nro)
alter table LOS_DEBATIENTES.cupones_por_pedidos add constraint uc_cup_ped_cup unique (cxp_cupon, cxp_pedido)
alter table LOS_DEBATIENTES.reclamos add constraint uc_rec unique (rec_pedido)
alter table LOS_DEBATIENTES.reclamos_por_cupones add constraint uc_rxc_rec unique (rxc_reclamo)
alter table LOS_DEBATIENTES.reclamos_por_cupones add constraint uc_rxc_cup unique (rxc_cupon)
alter table LOS_DEBATIENTES.direcciones_operadores add constraint uc_dio_descripcion unique (dio_descripcion)
alter table LOS_DEBATIENTES.estados_pedido add constraint uc_ep_descripcion unique (ep_descripcion)
alter table LOS_DEBATIENTES.dias add constraint uc_dia_descripcion unique (dia_descripcion)
alter table LOS_DEBATIENTES.tipos_de_pago add constraint uc_tdp_descripcion unique (tdp_descripcion)
alter table LOS_DEBATIENTES.estados_mensajeria add constraint uc_edm_descripcion unique (edm_descripcion)
alter table LOS_DEBATIENTES.tipos_de_movilidad add constraint uc_tdm_descripcion unique (tdm_descripcion)
alter table LOS_DEBATIENTES.tipos_de_reclamo add constraint uc_tdr_descripcion unique (tdr_descripcion)
alter table LOS_DEBATIENTES.tipos_de_local add constraint uc_tlc_nombre unique (tlc_nombre)
alter table LOS_DEBATIENTES.tipos_de_cupon add constraint uc_tdc_descripcion unique (tdc_descripcion)
alter table LOS_DEBATIENTES.estados_reclamo add constraint uc_er_descripcion unique (er_descripcion)
alter table LOS_DEBATIENTES.tipo_por_categoria add constraint uc_txc unique (txc_tipo_local, txc_categoria)
alter table LOS_DEBATIENTES.categorias add constraint uc_cat_descripcion unique (cat_descripcion)
alter table LOS_DEBATIENTES.zona_de_trabajo add constraint uc_zdt unique (zdt_localidad, zdt_repartidor)
alter table LOS_DEBATIENTES.localidades add constraint uc_lcd_descripcion unique (lcd_descripcion)

-- CREACION DE CHEKS

alter table LOS_DEBATIENTES.usuarios add constraint chk_usu_mail check (usu_mail like '%@%' and usu_mail like '%.%')
alter table LOS_DEBATIENTES.repartidores add constraint chk_rep_mail check (rep_email like '%@%' and rep_email like '%.%')
alter table LOS_DEBATIENTES.operadores add constraint chk_op_mail check (op_mail like '%@%' and op_mail like '%.%')
alter table LOS_DEBATIENTES.pedidos add constraint chk_ped_calificacion check (ped_calificacion > 0 and ped_calificacion < 6)
alter table LOS_DEBATIENTES.horarios add constraint chk_hor_hora_apertura check (hor_hora_apertura > 0 and hor_hora_apertura < 25)
alter table LOS_DEBATIENTES.horarios add constraint chk_hor_hora_cierre check (hor_hora_cierre > 0 and hor_hora_cierre < 25)
alter table LOS_DEBATIENTES.envios add constraint chk_env_propina check (env_propina >= 0)
alter table LOS_DEBATIENTES.envios add constraint chk_env_precio check (env_precio >= 0)
alter table LOS_DEBATIENTES.pedidos add constraint chk_ped_tarifa_servicio check (ped_tarifa_servicio >= 0)
alter table LOS_DEBATIENTES.pedidos add constraint chk_ped_total_cupones check (ped_total_cupones >= 0)
alter table LOS_DEBATIENTES.pedidos add constraint chk_ped_total_productos check (ped_total_productos >= 0)
alter table LOS_DEBATIENTES.productos add constraint chk_prd_precio check (prd_precio >= 0)
alter table LOS_DEBATIENTES.productos_por_pedidos add constraint chk_pxp_cantidad check (pxp_cantidad >= 0)
alter table LOS_DEBATIENTES.cupones add constraint chk_cup_monto check (cup_monto >= 0)
alter table LOS_DEBATIENTES.mensajerias add constraint chk_msj_calificacion check (msj_calificacion > 0 and msj_calificacion < 6)
alter table LOS_DEBATIENTES.mensajerias add constraint chk_msj_km check (msj_km >= 0)
alter table LOS_DEBATIENTES.mensajerias add constraint chk_msj_valor_asegurado check (msj_valor_asegurado >= 0)
alter table LOS_DEBATIENTES.mensajerias add constraint chk_msj_precio_env check (msj_precio_env >= 0)
alter table LOS_DEBATIENTES.mensajerias add constraint chk_msj_precio_seguro check (msj_precio_seguro >= 0)
alter table LOS_DEBATIENTES.mensajerias add constraint chk_msj_propina check (msj_propina >= 0)
alter table LOS_DEBATIENTES.mensajerias add constraint chk_msj_total check (msj_total >= 0)
alter table LOS_DEBATIENTES.mensajerias add constraint chk_msj_tiempo_estimado check (msj_tiempo_estimado >= 0)
alter table LOS_DEBATIENTES.tipos_de_paquete add constraint chk_paq_alto_max check (paq_alto_max >= 0)
alter table LOS_DEBATIENTES.tipos_de_paquete add constraint chk_paq_ancho_max check (paq_ancho_max >= 0)
alter table LOS_DEBATIENTES.tipos_de_paquete add constraint chk_paq_largo_max check (paq_largo_max >= 0)
alter table LOS_DEBATIENTES.tipos_de_paquete add constraint chk_paq_peso_max check (paq_peso_max >= 0)
alter table LOS_DEBATIENTES.tipos_de_paquete add constraint chk_paq_precio check (paq_precio >= 0)
alter table LOS_DEBATIENTES.reclamos add constraint chk_rec_calificacion check (rec_calificacion > 0 and rec_calificacion < 6)

-- CREACION DE INDICES

create index i_usu_dni ON LOS_DEBATIENTES.usuarios (usu_dni)
create index i_usu_telefono ON LOS_DEBATIENTES.usuarios (usu_telefono)
create index i_ped_numero ON LOS_DEBATIENTES.pedidos (ped_numero)
create index i_loc_nomYdir ON LOS_DEBATIENTES.locales (loc_nombre, loc_direccion)
create index i_uc_dirLocProvUsu ON LOS_DEBATIENTES.direcciones_usuarios (diu_provincia, diu_usuario)
create index i_dil_dirLocProv ON LOS_DEBATIENTES.direcciones_locales (dil_localidad, dil_provincia)
create index i_rep_dni ON LOS_DEBATIENTES.repartidores (rep_dni)
create index i_rep_telefono ON LOS_DEBATIENTES.repartidores (rep_telefono)
create index i_rep_email ON LOS_DEBATIENTES.repartidores (rep_email)
create index i_mdp_tipoTarjetaUsuario ON LOS_DEBATIENTES.medios_de_pago (mdp_tipo, mdp_nro_tarjeta, mdp_marca_tarjeta, mdp_usuario)
create index i_prd_codigoLocal ON LOS_DEBATIENTES.productos (prd_codigo, prd_local)
create index i_pxp_pedProd ON LOS_DEBATIENTES.productos_por_pedidos (pxp_pedido, pxp_producto)
create index i_ope_dni_tel_mail ON LOS_DEBATIENTES.operadores (op_dni, op_telefono, op_mail)
create index i_cup_num ON LOS_DEBATIENTES.cupones (cup_nro)
create index i_cxp_cupPed ON LOS_DEBATIENTES.cupones_por_pedidos (cxp_cupon, cxp_pedido)
create index i_rec_ped ON LOS_DEBATIENTES.reclamos (rec_pedido)
create index i_rxc_rec ON LOS_DEBATIENTES.reclamos_por_cupones (rxc_reclamo)
create index i_rxc_cup ON LOS_DEBATIENTES.reclamos_por_cupones (rxc_cupon)
create index i_dio_desc ON LOS_DEBATIENTES.direcciones_operadores (dio_descripcion)
create index i_ep_desc ON LOS_DEBATIENTES.estados_pedido (ep_descripcion)
create index i_dia_desc ON LOS_DEBATIENTES.dias (dia_descripcion)
create index i_tdp_desc ON LOS_DEBATIENTES.tipos_de_pago (tdp_descripcion)
create index i_edm_desc ON LOS_DEBATIENTES.estados_mensajeria (edm_descripcion)
create index i_tdm_desc ON LOS_DEBATIENTES.tipos_de_movilidad (tdm_descripcion)
create index i_tdr_desc ON LOS_DEBATIENTES.tipos_de_reclamo (tdr_descripcion)
create index i_tlc_nombre ON LOS_DEBATIENTES.tipos_de_local (tlc_nombre)
create index i_tdc_desc ON LOS_DEBATIENTES.tipos_de_cupon (tdc_descripcion)
create index i_er_desc ON LOS_DEBATIENTES.estados_reclamo (er_descripcion)
create index i_txc_locCat ON LOS_DEBATIENTES.tipo_por_categoria (txc_tipo_local, txc_categoria)
create index i_cat_desc ON LOS_DEBATIENTES.categorias (cat_descripcion)
create index i_zdt_locRep ON LOS_DEBATIENTES.zona_de_trabajo (zdt_localidad, zdt_repartidor)
create index i_lcd_desc ON LOS_DEBATIENTES.localidades (lcd_descripcion)
create index i_paq_id ON LOS_DEBATIENTES.tipos_de_paquete (paq_id)
create index i_dim_mens_des ON LOS_DEBATIENTES.direcciones_mensajerias (dim_dir_destino)
create index i_dim_mens_ori ON LOS_DEBATIENTES.direcciones_mensajerias (dim_dir_origen)
create index i_dim_mens_prov ON LOS_DEBATIENTES.direcciones_mensajerias (dim_provincia)
GO

-- CREACION DE PROCEDURES PARA MIGRACION DE DATOS DE TABLA MAESTRA
-- CADA PROCEDURE MIGRA UNA TABLA EN ESPECIFICO

-- LOS_DEBATIENTES.usuarios
CREATE PROCEDURE LOS_DEBATIENTES.migracion_usuarios
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.usuarios select distinct 
		USUARIO_NOMBRE usu_nombre, 
		USUARIO_APELLIDO usu_apellido,
		USUARIO_DNI usu_dni,
		USUARIO_FECHA_REGISTRO usu_fecha_registro,
		USUARIO_TELEFONO usu_telefono,
		USUARIO_MAIL usu_mail,
		USUARIO_FECHA_NAC usu_fecha_nacimiento
	from gd_esquema.Maestra with (nolock) where USUARIO_NOMBRE is not null
END
GO

-- LOS_DEBATIENTES.tipos_de_local
CREATE PROCEDURE LOS_DEBATIENTES.migracion_tipos_de_local
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.tipos_de_local select distinct 
		LOCAL_TIPO tlc_nombre
	from gd_esquema.Maestra with (nolock) where LOCAL_TIPO is not null
END
GO

-- LOS_DEBATIENTES.localidades
CREATE PROCEDURE LOS_DEBATIENTES.migracion_localidades
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.localidades select distinct 
		DIRECCION_USUARIO_LOCALIDAD lcd_descripcion
	from gd_esquema.Maestra with (nolock) where DIRECCION_USUARIO_LOCALIDAD is not null
	UNION select distinct 
		LOCAL_LOCALIDAD lcd_descripcion
	from gd_esquema.Maestra with (nolock) where LOCAL_LOCALIDAD is not null
	UNION select distinct 
		ENVIO_MENSAJERIA_LOCALIDAD lcd_descripcion
	from gd_esquema.Maestra with (nolock) where ENVIO_MENSAJERIA_LOCALIDAD is not null
END
GO

-- LOS_DEBATIENTES.direcciones_usuarios
CREATE PROCEDURE LOS_DEBATIENTES.migracion_direcciones_usuarios
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.direcciones_usuarios select distinct 
		DIRECCION_USUARIO_DIRECCION dir_direccion,
		lcd_id  dir_localidad,
		DIRECCION_USUARIO_PROVINCIA dir_provincia,
		usu_id dir_usuario,
		DIRECCION_USUARIO_NOMBRE
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = DIRECCION_USUARIO_LOCALIDAD)
	inner join LOS_DEBATIENTES.usuarios with (nolock) on ( usu_dni = USUARIO_DNI)
END
GO

-- LOS_DEBATIENTES.direcciones_locales
CREATE PROCEDURE LOS_DEBATIENTES.migracion_direcciones_locales
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.direcciones_locales select distinct 
		LOCAL_DIRECCION dir_direccion,
		lcd_id dir_localidad,
		LOCAL_PROVINCIA dir_provincia
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = LOCAL_LOCALIDAD)
END
GO

-- LOS_DEBATIENTES.direcciones_operadores
CREATE PROCEDURE LOS_DEBATIENTES.migracion_direcciones_operadores
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.direcciones_operadores select distinct 
		OPERADOR_RECLAMO_DIRECCION dio_descripcion
	from gd_esquema.Maestra with (nolock) where OPERADOR_RECLAMO_DIRECCION is not null
END
GO

-- LOS_DEBATIENTES.tipos_de_reclamo
CREATE PROCEDURE LOS_DEBATIENTES.migracion_tipos_de_reclamo
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.tipos_de_reclamo select distinct 
		RECLAMO_TIPO tdr_descripcion
	from gd_esquema.Maestra with (nolock) where RECLAMO_TIPO is not null
END
GO

-- LOS_DEBATIENTES.tipos_de_pago
CREATE PROCEDURE LOS_DEBATIENTES.migracion_tipos_de_pago
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.tipos_de_pago select distinct 
		MEDIO_PAGO_TIPO tdr_descripcion
	from gd_esquema.Maestra with (nolock) where MEDIO_PAGO_TIPO is not null
END
GO

-- LOS_DEBATIENTES.tipos_de_movilidad
CREATE PROCEDURE LOS_DEBATIENTES.migracion_tipos_de_movilidad
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.tipos_de_movilidad select distinct 
		REPARTIDOR_TIPO_MOVILIDAD tdm_descripcion
	from gd_esquema.Maestra with (nolock) where REPARTIDOR_TIPO_MOVILIDAD is not null
END
GO

-- LOS_DEBATIENTES.repartidores
CREATE PROCEDURE LOS_DEBATIENTES.migracion_repartidores
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.repartidores select distinct 
		REPARTIDOR_NOMBRE rep_nombre,
		REPARTIDOR_APELLIDO rep_apellido,
		REPARTIDOR_DNI rep_dni,
		REPARTIDOR_TELEFONO rep_telefono,
		REPARTIDOR_DIRECION rep_direccion,
		REPARTIDOR_EMAIL rep_email,
		REPARTIDOR_FECHA_NAC rep_fecha_nacimiento,
		tdm_id rep_tipo_movilidad
	from gd_esquema.Maestra with (nolock) 
	inner join LOS_DEBATIENTES.tipos_de_movilidad with (nolock) on (tdm_descripcion = REPARTIDOR_TIPO_MOVILIDAD)
END
GO

-- LOS_DEBATIENTES.zona_de_trabajo
CREATE PROCEDURE LOS_DEBATIENTES.migracion_zona_de_trabajo
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.zona_de_trabajo select distinct
		lcd_id zdt_localidad,
		rep_id zdt_repartidor,
		iif(lag(rep_id) over (order by rep_id, max(PEDIDO_FECHA) desc) = rep_id, 0, 1) zdt_activo
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = LOCAL_LOCALIDAD)
	inner join LOS_DEBATIENTES.repartidores with (nolock) on (rep_dni = REPARTIDOR_DNI)
	group by lcd_id, rep_id
END
GO

-- LOS_DEBATIENTES.estados_reclamo
CREATE PROCEDURE LOS_DEBATIENTES.migracion_estados_reclamo
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.estados_reclamo select distinct RECLAMO_ESTADO
	from gd_esquema.Maestra with (nolock) where RECLAMO_ESTADO is not null
END
GO

-- LOS_DEBATIENTES.estados_pedido
CREATE PROCEDURE LOS_DEBATIENTES.migracion_estados_pedido
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.estados_pedido select distinct PEDIDO_ESTADO
	from gd_esquema.Maestra with (nolock) where PEDIDO_ESTADO is not null
END
GO

-- LOS_DEBATIENTES.estados_mensajeria
CREATE PROCEDURE LOS_DEBATIENTES.migracion_estados_mensajeria
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.estados_mensajeria select distinct ENVIO_MENSAJERIA_ESTADO
	from gd_esquema.Maestra with (nolock) where ENVIO_MENSAJERIA_ESTADO is not null
END
GO

-- LOS_DEBATIENTES.dias
CREATE PROCEDURE LOS_DEBATIENTES.migracion_dias
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.dias select distinct HORARIO_LOCAL_DIA
	from gd_esquema.Maestra with (nolock) where HORARIO_LOCAL_DIA is not null
END
GO

-- LOS_DEBATIENTES.locales
CREATE PROCEDURE LOS_DEBATIENTES.migracion_locales
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.locales select distinct 
		LOCAL_NOMBRE loc_nombre,
		LOCAL_DESCRIPCION loc_descripcion,
		dil_id loc_direccion,
		tlc_id loc_tipo
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = LOCAL_LOCALIDAD)
	inner join LOS_DEBATIENTES.direcciones_locales with (nolock) on (dil_direccion = LOCAL_DIRECCION and dil_provincia = LOCAL_PROVINCIA and dil_localidad = lcd_id)
	inner join LOS_DEBATIENTES.tipos_de_local with (nolock) on (tlc_nombre = LOCAL_TIPO)
END
GO

-- LOS_DEBATIENTES.horarios
CREATE PROCEDURE LOS_DEBATIENTES.migracion_horarios
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.horarios select distinct 
		HORARIO_LOCAL_HORA_APERTURA hor_hora_apertura,
		HORARIO_LOCAL_HORA_CIERRE hor_hora_cierre,
		dia_id hor_dia,
		loc_id hor_local
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.dias with (nolock) on (dia_descripcion = HORARIO_LOCAL_DIA)
	inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = LOCAL_LOCALIDAD)
	inner join LOS_DEBATIENTES.direcciones_locales with (nolock) on (dil_direccion = LOCAL_DIRECCION and dil_provincia = LOCAL_PROVINCIA and dil_localidad = lcd_id)
	inner join LOS_DEBATIENTES.locales with (nolock) on (LOCAL_NOMBRE = loc_nombre and loc_direccion = dil_id)
END
GO

-- LOS_DEBATIENTES.medios_de_pago
CREATE PROCEDURE LOS_DEBATIENTES.migracion_medios_de_pago
AS 
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.medios_de_pago select distinct 
		MEDIO_PAGO_NRO_TARJETA mdp_nro_tarjeta,
		tdp_id mdp_tipo,
		MARCA_TARJETA mdp_marca_tarjeta,
		usu_id mdp_usuario
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.tipos_de_pago with (nolock) on (tdp_descripcion = MEDIO_PAGO_TIPO)
	inner join LOS_DEBATIENTES.usuarios with (nolock) on (usu_dni = USUARIO_DNI)
END
GO

-- LOS_DEBATIENTES.tipos_de_cupon
CREATE PROCEDURE LOS_DEBATIENTES.migracion_tipos_de_cupon
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.tipos_de_cupon select distinct 
		CUPON_TIPO cup_descripcion
	from gd_esquema.Maestra with (nolock) where CUPON_TIPO is not null
END
GO

-- LOS_DEBATIENTES.cupones
CREATE PROCEDURE LOS_DEBATIENTES.migracion_cupones
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.cupones select distinct 
		CUPON_NRO cup_nro,
		CUPON_MONTO cup_monto ,
		CUPON_FECHA_ALTA cup_fecha_alta,
		CUPON_FECHA_VENCIMIENTO cup_fecha_vencimiento,
		tdc_id cup_tipo
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.tipos_de_cupon with (nolock) on (tdc_descripcion = CUPON_TIPO)
END
GO

-- LOS_DEBATIENTES.tipos_de_paquete
CREATE PROCEDURE LOS_DEBATIENTES.migracion_tipos_de_paquete
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.tipos_de_paquete select distinct 
		PAQUETE_TIPO paq_tipo,
		PAQUETE_ALTO_MAX paq_alto_max,
		PAQUETE_ANCHO_MAX paq_ancho_max,
		PAQUETE_LARGO_MAX paq_largo_max,
		PAQUETE_PESO_MAX paq_peso_max,
		PAQUETE_TIPO_PRECIO paq_precio
	from gd_esquema.Maestra with (nolock) where PAQUETE_TIPO is not null
END
GO

-- LOS_DEBATIENTES.productos
CREATE PROCEDURE LOS_DEBATIENTES.migracion_productos
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.productos select distinct
		PRODUCTO_LOCAL_CODIGO  prd_codigo,
		loc_id prd_local,
		PRODUCTO_LOCAL_NOMBRE prd_nombre,
		PRODUCTO_LOCAL_DESCRIPCION prd_descripcion,
		PRODUCTO_LOCAL_PRECIO prd_precio
	from gd_esquema.Maestra with (nolock) 
    inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = DIRECCION_USUARIO_LOCALIDAD)
    inner join LOS_DEBATIENTES.direcciones_locales with (nolock) on (dil_direccion = LOCAL_DIRECCION and dil_provincia = LOCAL_PROVINCIA and dil_localidad = lcd_id)
    inner join LOS_DEBATIENTES.locales with (nolock) on (loc_nombre = LOCAL_NOMBRE and loc_direccion = dil_id)
	where PRODUCTO_LOCAL_CODIGO is not null
END
GO

-- LOS_DEBATIENTES.pedidos
CREATE PROCEDURE LOS_DEBATIENTES.migracion_pedidos
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.pedidos select distinct
		PEDIDO_NRO ped_numero,
		usu_id ped_usuario,
		loc_id ped_local,
		PEDIDO_TARIFA_SERVICIO ped_tarifa_servicio,
		PEDIDO_TOTAL_SERVICIO ped_total_servicio,
		PEDIDO_OBSERV ped_observaciones,
		PEDIDO_FECHA ped_fecha,
		PEDIDO_FECHA_ENTREGA ped_fecha_entrega,
		PEDIDO_TIEMPO_ESTIMADO_ENTREGA ped_tiempo_estimado_entrega,
		PEDIDO_CALIFICACION ped_calificacion,
		ep_id ped_estado,
		mdp_id ped_medio_pago,
		PEDIDO_TOTAL_CUPONES ped_total_cupones,
		PEDIDO_TOTAL_PRODUCTOS ped_total_productos
	from gd_esquema.Maestra with (nolock) 
    inner join LOS_DEBATIENTES.usuarios with (nolock) on (usu_dni = USUARIO_DNI)
    inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = DIRECCION_USUARIO_LOCALIDAD)
    inner join LOS_DEBATIENTES.direcciones_locales with (nolock) on (dil_direccion = LOCAL_DIRECCION and dil_provincia = LOCAL_PROVINCIA and dil_localidad = lcd_id)
    inner join LOS_DEBATIENTES.locales with (nolock) on (loc_nombre = LOCAL_NOMBRE and loc_direccion = dil_id)
    inner join LOS_DEBATIENTES.estados_pedido with (nolock) on (ep_descripcion = PEDIDO_ESTADO)
    inner join LOS_DEBATIENTES.tipos_de_pago with (nolock) on (tdp_descripcion = MEDIO_PAGO_TIPO)
    inner join LOS_DEBATIENTES.medios_de_pago with (nolock) on (mdp_tipo = tdp_id and mdp_usuario = usu_id and 
		mdp_nro_tarjeta = MEDIO_PAGO_NRO_TARJETA and mdp_marca_tarjeta = MARCA_TARJETA)
END
GO

-- LOS_DEBATIENTES.envios
CREATE PROCEDURE LOS_DEBATIENTES.migracion_envios
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.envios select distinct 
		diu_id env_direccion,
		PEDIDO_PRECIO_ENVIO env_precio,
		PEDIDO_PROPINA env_propina,
		rep_id env_repartidor,
		ped_id env_pedido
	from gd_esquema.Maestra with (nolock)
    inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = DIRECCION_USUARIO_LOCALIDAD)
    inner join LOS_DEBATIENTES.usuarios with (nolock) on (usu_dni = USUARIO_DNI)
    inner join LOS_DEBATIENTES.direcciones_usuarios with (nolock) on diu_direccion = DIRECCION_USUARIO_DIRECCION and 
		diu_provincia = DIRECCION_USUARIO_PROVINCIA and diu_localidad = lcd_id and diu_usuario = usu_id
    inner join LOS_DEBATIENTES.repartidores with (nolock) on (rep_dni = REPARTIDOR_DNI)
    inner join LOS_DEBATIENTES.pedidos with (nolock) on (ped_numero = PEDIDO_NRO)
END
GO

-- LOS_DEBATIENTES.operadores
CREATE PROCEDURE LOS_DEBATIENTES.migracion_operadores
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.operadores select distinct 
		OPERADOR_RECLAMO_NOMBRE op_nombre,
		OPERADOR_RECLAMO_APELLIDO op_apellido,
		OPERADOR_RECLAMO_DNI op_dni,
		OPERADOR_RECLAMO_TELEFONO op_telefono,
		dio_id op_direccion,
		OPERADOR_RECLAMO_MAIL op_mail,
		OPERADOR_RECLAMO_FECHA_NAC op_fecha_nacimiento
	from gd_esquema.Maestra with (nolock)
    inner join LOS_DEBATIENTES.direcciones_operadores with (nolock) on (dio_descripcion = OPERADOR_RECLAMO_DIRECCION)
END
GO

-- LOS_DEBATIENTES.reclamos
CREATE PROCEDURE LOS_DEBATIENTES.migracion_reclamos
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.reclamos select distinct 
		usu_id rec_usuario,
		RECLAMO_FECHA rec_fecha,
		RECLAMO_DESCRIPCION rec_descripcion,
		RECLAMO_FECHA_SOLUCION rec_fecha_solucion,
		RECLAMO_SOLUCION rec_solucion,
		RECLAMO_CALIFICACION rec_calificacion,
		tdr_id rec_tipo,
		er_id rec_estado,
		ped_id rec_pedido,
		op_id rec_operador,
		 loc_id rec_local
	from gd_esquema.Maestra with (nolock)
    inner join LOS_DEBATIENTES.usuarios with (nolock) on (usu_dni = USUARIO_DNI)
    inner join LOS_DEBATIENTES.tipos_de_reclamo with (nolock) on (tdr_descripcion = RECLAMO_TIPO)
    inner join LOS_DEBATIENTES.estados_reclamo with (nolock) on (er_descripcion = RECLAMO_ESTADO)
    inner join LOS_DEBATIENTES.pedidos with (nolock) on (ped_numero = PEDIDO_NRO)
    inner join LOS_DEBATIENTES.operadores with (nolock) on (op_dni = OPERADOR_RECLAMO_DNI and op_telefono = OPERADOR_RECLAMO_TELEFONO)
	inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = LOCAL_LOCALIDAD)
	inner join LOS_DEBATIENTES.direcciones_locales with (nolock) on (dil_direccion = LOCAL_DIRECCION and dil_localidad = lcd_id and dil_provincia = LOCAL_PROVINCIA)
	inner join LOS_DEBATIENTES.locales with (nolock) on (loc_nombre = LOCAL_NOMBRE and loc_direccion = dil_id)
END
GO

-- LOS_DEBATIENTES.direcciones_mensajerias
CREATE PROCEDURE LOS_DEBATIENTES.migracion_direcciones_mensajerias
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.direcciones_mensajerias select distinct
		ENVIO_MENSAJERIA_DIR_ORIG dim_dir_origen,
		ENVIO_MENSAJERIA_DIR_DEST dim_dir_destino,
		lcd_id dim_localidad,
		ENVIO_MENSAJERIA_PROVINCIA dim_provincia
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = ENVIO_MENSAJERIA_LOCALIDAD)
END
GO

-- LOS_DEBATIENTES.mensajerias
CREATE PROCEDURE LOS_DEBATIENTES.migracion_mensajerias
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.mensajerias select distinct
		dim_id msj_direccion,
		ENVIO_MENSAJERIA_KM msj_km,
		ENVIO_MENSAJERIA_VALOR_ASEGURADO msj_valor_asegurado,
		ENVIO_MENSAJERIA_PRECIO_ENVIO msj_precio_env,
		ENVIO_MENSAJERIA_PRECIO_SEGURO msj_precio_seguro,
		ENVIO_MENSAJERIA_PROPINA msj_propina,
		ENVIO_MENSAJERIA_TOTAL msj_total,
		ENVIO_MENSAJERIA_OBSERV msj_observaciones,
		ENVIO_MENSAJERIA_FECHA msj_fecha,
		ENVIO_MENSAJERIA_FECHA_ENTREGA msj_fecha_entrega,
		ENVIO_MENSAJERIA_TIEMPO_ESTIMADO msj_tiempo_estimado,
		ENVIO_MENSAJERIA_CALIFICACION msj_calificacion,
		usu_id msj_usuario,
		paq_id msj_tipo_de_paquete,
		rep_id msj_repartidor,
		mdp_id  msj_medio_de_pago,
		edm_id msj_estado
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.direcciones_mensajerias with (nolock) on (dim_dir_origen = ENVIO_MENSAJERIA_DIR_ORIG and 
		dim_dir_destino = ENVIO_MENSAJERIA_DIR_DEST and dim_provincia = ENVIO_MENSAJERIA_PROVINCIA)
	inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = ENVIO_MENSAJERIA_LOCALIDAD and dim_localidad = lcd_id)
	inner join LOS_DEBATIENTES.usuarios with (nolock) on (usu_dni = USUARIO_DNI)
	inner join LOS_DEBATIENTES.tipos_de_paquete with (nolock) on (paq_tipo = PAQUETE_TIPO)
	inner join LOS_DEBATIENTES.repartidores with (nolock) on (rep_dni = REPARTIDOR_DNI)
	inner join LOS_DEBATIENTES.tipos_de_pago with (nolock) on (tdp_descripcion = MEDIO_PAGO_TIPO)
	inner join LOS_DEBATIENTES.medios_de_pago with (nolock) on (mdp_tipo = tdp_id and mdp_usuario = usu_id and 
		mdp_nro_tarjeta = MEDIO_PAGO_NRO_TARJETA and mdp_marca_tarjeta = MARCA_TARJETA)
	inner join LOS_DEBATIENTES.estados_mensajeria with (nolock) on (edm_descripcion = ENVIO_MENSAJERIA_ESTADO)
END
GO

-- LOS_DEBATIENTES.reclamos_por_cupones
CREATE PROCEDURE LOS_DEBATIENTES.migracion_reclamos_por_cupones
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.reclamos_por_cupones select distinct
		rec_id rxc_reclamo,
		cup_id rxc_cupon
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.pedidos with (nolock) on (ped_numero = PEDIDO_NRO)
	inner join LOS_DEBATIENTES.reclamos with (nolock) on (rec_pedido = ped_id)
	inner join LOS_DEBATIENTES.cupones with (nolock) on (cup_nro = CUPON_NRO)
END
GO

-- LOS_DEBATIENTES.productos_por_pedidos
CREATE PROCEDURE LOS_DEBATIENTES.migracion_productos_por_pedidos
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.productos_por_pedidos select distinct
		ped_id pxp_pedido,
		prd_id pxp_producto,
		SUM(PRODUCTO_CANTIDAD) pxp_cantidad,
		MIN(PRODUCTO_LOCAL_PRECIO) pxp_precio
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.pedidos with (nolock) on (ped_numero = PEDIDO_NRO)
	inner join LOS_DEBATIENTES.productos with (nolock) on (prd_codigo = PRODUCTO_LOCAL_CODIGO)
	inner join LOS_DEBATIENTES.locales with (nolock) on (prd_local = loc_id and loc_nombre = LOCAL_NOMBRE)
	inner join LOS_DEBATIENTES.direcciones_locales with (nolock) on (loc_direccion = dil_id and dil_direccion = LOCAL_DIRECCION and dil_provincia = LOCAL_PROVINCIA)
	inner join LOS_DEBATIENTES.localidades with (nolock) on (lcd_descripcion = LOCAL_LOCALIDAD and dil_localidad = lcd_id)
	group by ped_id, prd_id
END
GO

-- LOS_DEBATIENTES.cupones_por_pedidos
CREATE PROCEDURE LOS_DEBATIENTES.migracion_cupones_por_pedidos
AS
BEGIN
	SET NOCOUNT ON;
	insert LOS_DEBATIENTES.cupones_por_pedidos select distinct
		cup_id cxp_cupon,
		ped_id cxp_pedido
	from gd_esquema.Maestra with (nolock)
	inner join LOS_DEBATIENTES.cupones with (nolock) on (cup_nro = CUPON_NRO)
	inner join LOS_DEBATIENTES.pedidos with (nolock) on (ped_numero = PEDIDO_NRO)
END
GO

-- EJECUCION DE PROCEDURES CREADOS

EXEC LOS_DEBATIENTES.migracion_cupones_por_pedidos
EXEC LOS_DEBATIENTES.migracion_usuarios
EXEC LOS_DEBATIENTES.migracion_tipos_de_local
EXEC LOS_DEBATIENTES.migracion_localidades
EXEC LOS_DEBATIENTES.migracion_direcciones_usuarios
EXEC LOS_DEBATIENTES.migracion_direcciones_locales
EXEC LOS_DEBATIENTES.migracion_direcciones_operadores
EXEC LOS_DEBATIENTES.migracion_tipos_de_reclamo
EXEC LOS_DEBATIENTES.migracion_tipos_de_pago
EXEC LOS_DEBATIENTES.migracion_tipos_de_movilidad
EXEC LOS_DEBATIENTES.migracion_repartidores
EXEC LOS_DEBATIENTES.migracion_zona_de_trabajo
EXEC LOS_DEBATIENTES.migracion_estados_reclamo
EXEC LOS_DEBATIENTES.migracion_estados_pedido
EXEC LOS_DEBATIENTES.migracion_estados_mensajeria
EXEC LOS_DEBATIENTES.migracion_dias
EXEC LOS_DEBATIENTES.migracion_locales
EXEC LOS_DEBATIENTES.migracion_horarios
EXEC LOS_DEBATIENTES.migracion_medios_de_pago
EXEC LOS_DEBATIENTES.migracion_tipos_de_cupon
EXEC LOS_DEBATIENTES.migracion_cupones
EXEC LOS_DEBATIENTES.migracion_tipos_de_paquete
EXEC LOS_DEBATIENTES.migracion_productos
EXEC LOS_DEBATIENTES.migracion_pedidos
EXEC LOS_DEBATIENTES.migracion_envios
EXEC LOS_DEBATIENTES.migracion_operadores
EXEC LOS_DEBATIENTES.migracion_reclamos
EXEC LOS_DEBATIENTES.migracion_direcciones_mensajerias
EXEC LOS_DEBATIENTES.migracion_mensajerias
EXEC LOS_DEBATIENTES.migracion_reclamos_por_cupones
EXEC LOS_DEBATIENTES.migracion_productos_por_pedidos