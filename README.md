# Gestión de Canchas

Sistema desarrollado en C++ para la administración de alquiler de canchas, permitiendo gestionar clientes, turnos y registros de manera organizada.

---

# Funcionalidades principales

El sistema permite:

- Gestionar clientes (alta, baja, modificación y consulta)  
- Administrar canchas (registro, edición, eliminación y consulta)  
- Registrar y gestionar alquileres con control de disponibilidad por fecha y hora
- Control de disponibilidad horaria para evitar superposición de reservas  
- Búsqueda de información (clientes, canchas y alquileres) mediante distintos criterios  
- Gestión de pagos, incluyendo señas y estado de las reservas  
- Validación de datos ingresados por el usuario  
- Almacenamiento persistente de la información mediante archivos    

---

# Tecnologías utilizadas

- C++  
- rlutil (para interfaz en consola)  

---

# Descripción

Este proyecto fue desarrollado como trabajo práctico, con el objetivo de simular un sistema real de gestión de canchas.  
Se implementa lógica modular, separación de responsabilidades y manejo de datos mediante archivos.

---

# Proyecto realizado en conjunto:

- Thiago Vazquez - desarrollo de la lógica del sistema  
- Julian Ugoletti - interfaz visual utilizando rlutil  

---

# Estructura del proyecto

El proyecto se organiza en módulos separados para mejorar la mantenibilidad:

- clases: entidades principales del sistema  
- logica: gestión de archivos y operaciones  
- menus: interfaz de usuario  
- utils: validaciones y funciones auxiliares  


---

# Estado del proyecto

- Funcional  
- Posibles mejoras futuras:
- Integración con base de datos  
- Automatización con Python e IA  

---

# Nota

- Este proyecto forma parte de mi aprendizaje en programación y desarrollo de sistemas en C++. 
- Dejé el informe del proyecto en Word. Hay ideas que surgieron durante el desarrollo que no se detallaron a fondo en el documento final.
