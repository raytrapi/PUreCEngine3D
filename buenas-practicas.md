= Código de buenas prácticas

Existen tantas formas de programar como desarrolladores o personas, y aunque todas son válidas cuando nos enfrentamos a un desarrollo con un grupo de personas es recomendable definir la reglas que deberán respetarse para que el trabajo se ejecute de la mejor forma posible.
Estas pautas que deberán ser consensuadas por todos, tienen como objetivo dos cuestiones importantes, la buena relación dentro del grupo y el desarrollo de un código limpio.

== Convivencia

Este apartado viene a completar el “Código de Conducta convenido para Contribuyentes” en el que se indican las pautas generales en relación al trato con terceras personas y el cómo se deberá relacionar el equipo integrante en el proyecto cuando lo haga en nombre de este.

Aquí se indicarán aquellas normas que regularán la convivencia entre los y las integrantes debido a la diversidad de roles y niveles del grupo.

Por un lado se deberá asumir que no todos y todas los y las integrantes disponen de un nivel adecuado o suficiente para la realización del trabajo, existiendo además roles que no aporten inicialmente nada al proyecto.
L@s integrantes con mayor capacidad deberán respetar y comprender el trabajo desarrollado por l@s de menor capacidad, debiendo aconsejar en la medida de lo posible a est@s últimos para que puedan adquirir los conocimientos o aptitudes adecuadas. Por otro lado, l@s integrantes de menor capacidad deberán de esforzarse en comprender e intentar mejorar en las aptitudes que le sean requeridas.

Tod@s l@s integrantes tendrán la capacidad de aportar mejoras o críticas constructivas ante el desarrollo o ideas de l@s demás. L@s integrantes a l@s que se le han realizado dichas mejoras o críticas deberán tomarlas como algo positivo, debiendo analizarlas y responderlas, bien con las correcciones o adaptaciones sugeridas o bien con una justificación razonada al respecto. El resto de integrantes podrán ayudar en la resolución de estas situaciones.

== Desarrollo del código

A continuación se definirán una serie de reglas y convenciones que pretenden unificar el código desarrollado por el equipo. Estas reglas han sido tomadas en base a la experiencia y algunas no tienen una justificación más allá de una mejor comprensión del código.

=== Reglas

Deberemos tener presente que el desarrollo de nuestro proyecto podrá sufrir modificaciones tanto a nivel de funcionamiento como a nivel de requerimientos del sistema en el que se encuentre instalado. Todo esto implica que nuestro proyecto deberá disponer de un mantenimiento que le dé continuidad en el tiempo.

Teniendo en cuenta lo anterior, deberemos anticiparnos a estos cambios revisando y analizando todos los métodos que utilicemos para intentar mejorarlo tanto en el funcionamiento del mismo como en su documentación . 
La regla de oro es que nada es de nadie y todo es de todos, por lo que si se encuentra algo dentro del proyecto que está mal, o que se puede mejorar, no debemos dudar en realizar la mejora. Esta situación será reportada al autor o autora para que pueda tomar consciencia del cambio.

=== Convenciones

Cada lenguaje de programación puede disponer de convenios propios que de alguna manera redefinen los aquí indicados. En ese caso se decidirá entre todos los y las componentes del equipo el convenio a seguir.

A continuación se definen los convenios generales que regirán el desarrollo del código.

==== Indentación

Por norma general se utilizarán 3 espacios como elemento de indentación. En la mayoría de los lenguajes, excluyendo a Python y Cobol, la indentación es simplemente un mecanismo de mejora visual por lo que no afecta al resultado final del código.

Existe un debate relacionado en el uso de tabuladores o espacios, sin embargo los IDE (Los Entornos de Desarrollo Integrados) permiten definir los tabuladores como espacios. Aquell@s que estén acostumbrados a utilizar tabulación como elemento de indentación deberán hacer el ajuste oportuno para que el IDE lo transforme en espacios.

Las publicaciones en producción deberán tener los códigos minimizados para evitar una sobrecarga en los clientes.

==== Llaves

Las llaves se colocarán en la misma línea de cada instrucción. De igual forma, las sentencias que pertenecen a la misma instrucción deberán colocarse en la misma línea que el cierre de la sentencia (por ejemplo en la palabra clave “else”).
Toda secuencia condicional deberá estar encerrada entre llaves.

// Flujo condicional Sí
if (condicion){
   sentencia;
}

// Flujo condicional Sí-Entonces

if (condicion){
   sentencia;
   sentencia;
}else{
   sentencia;
}

==== Ámbito de las variables

Se deberá huir de utilizar variables globales. En el caso de que se requiera el uso de este tipo de variables se deberá crear un único objeto estático que almacene estos valores.

==== Formato de nombres de variables y métodos

Se utilizará camelCase para el nombre de variables y métodos.
Se utilizará PascalCase pare el nombre de clases.
Se utilizará MAYÚSCULAS para las constantes.
Se utilizará snake_case para los nombre de tablas de base de datos.

===== Variable

Aunque en términos generales la recomendación es utilizar el inglés para definir el nombre de las variables, para este proyecto utilizaremos variables en español. 

Como regla general el nombre de cada variable deberá identificar claramente su objetivo y evitando utilizar nombre cortos. Se permite el uso de nombres cortos para variables de propósito general como “i”, “j”, “k” utilizados para iteraciones o “x”, y”, “z” para almacenar coordenadas.

===== Métodos (funciones y procedimientos)

Al igual que las variables, las funciones tendrán nombres que informen de la acción que realizarán.
Al representar acciones seguramente contendrán un verbo. Este deberá escribirse en infinitivo. (leer, escribir, guardar, ….)

===== Clases

Las propiedades de las clases deberán ser privadas o protegidas (dependiendo de la necesidad) en ningún caso se deberán utilizar variables públicas.

====== Observadores y modificadores

Siguiendo el convenio de utilizar nombre de variables y métodos en español, se mantendrá la misma norma para los observadores (getter) y los modificadores (setter). Estos métodos serán los únicos puntos de acceso a los valores de las propiedades de la clase.

Se usará “cogerNombreVariable” para observar el valor de la variable. Esto otorgará a la propiedad la característica de lectura. 
Se usará “ponerNombreVariable” para modificar el valor de la variable. Esto otorgará a la propiedad  la característica de escritura.
Si la propiedad es booleana (sólo admite un valor de verdadero o falso) se utilizará para el observador la sintaxis “esNombreVariable”.

El siguiente ejemplo muestra cómo se define una clase en español y en inglés.

**Ejemplo en inglés**
class Person{
   private string name;
   private date birthday;
   private bool married;
  
   public Person(string name, date birthday, bool married); //constructor
   public string getName(); //get name
   public void setName(string name); //set name
  
   public date getBirthday(); //get birthday
   public void setBirthday(date birthday); //set birthday
   
   public bool isMarried(); //get married
   public void setMarried(bool married); //set married
}

**Ejemplo en español**
class Persona{
   private string nombre;
   private date fechaNacimiento;
   private bool casado;
  
   public Persona(string nombre, date fechaNacimiento, bool casado); //constructor
   public string cogerNombre(); //coger nombre
   public void ponerNombre(string nombre); //poner nombre
  
   public date cogerFechaNacimiento(); //coger fecha de nacimiento
   public void ponerFechaNacimiento(date fehchaNacimiento); //poner fecha de nacimiento
   
   public bool esCasado(); //get casado
   public void ponerCasado(bool casado); //poner casado
}
==== Condicionales

===== Minimizar condiciones

Se deberán realizar condicionales con el menor coste posible, por ello es preferible utilizar el operador igual “=” al operador distinto “!=”. Lo anterior implica que el nombre de las variables deberán ser adecuadas para facilitar la comprensión del código.

**Correcto**

bool pendiente=true;
while (pendiente){
   // Hacer algo
}

**Mejorable**

bool terminado=false;
while (!teminado){ // Aquí hacemos una operación de negado adicional.
   // Hacer algo
}

===== Paréntesis

Todas las condiciones deberán estar encerradas entre paréntesis.

**Correcto**

bool pendiente=true;
if (pendiente){
   // Hacer algo
}

**Incorrecto**

bool pendiente=true;
if pendiente{
   // Hacer algo
}

===== Operador ternario

El operador ternario se deberá dividir en varias líneas.

**Correcto** 

var valor = (a === b)
   ? 1
   : 2;

**Incorrecto**

var valor = (a === b) ? 1 : 2;

===== Utilizar condiciones descriptivas

Cualquier condición no trivial debe asignarse a una variable o función con nombre descriptivo.

**Correcto**

bool claveValida = (clave.length >= 4 && clave==”yo”);

if (claveValida) {
   // Procesar
}

**Incorrecto**

if (clave.length >= 4 && clave==”yo”) {
   // Procesar
}

==== Comentarios

Para una buena comprensión futura del código se deberán realizar aquellos comentarios necesarios. No se deberá abusar de estos comentarios por lo que solo se indicará aquella información o lógica que no se extraiga propiamente de la lectura del código.
Si hemos escogido nombres adecuados y auto-descriptivos, no será necesario añadir un comentario adicional si este no aporta algún matiz que no se pueda extraer del propio nombre.

===== Comentarios de documentación

Existen herramientas que extraen información del código y son capaces de generar una documentación adecuada. Aunque estas herramientas suelen tener una sintaxis concreta la mayoría siguen estos principios básicos. 
Los comentarios para documentación empiezan con «/**»

====== Clases

/**
*  Descripción de la clase
*  @author Nombre del autor de la clase
*/

====== Variable

/**
* Descripción de la variable
*/

====== Método

/**
* Descripción del método
* @param tipo NombreParámetro descripción
* @param ...
*
* @return tipo
*/

**Más información:**

/**
* Descripción del método
* @param tipo NombreParámetro descripción
* @param ...
*
* @return tipo
*
* @see Enlace con información detallada del método
* @since Número de versión desde la que está implementado el método
* @version Número de versión de este método
* @throws En el caso de generar excepciones, aquí se indicará la naturaleza del mismo
*
* @deprecated Esto marca que el método ya está depreciado.
*/

====== Tareas

Se podrán definir tareas para realizar en el futuro, para esto se usarán marcas especiales que la mayoría de los IDE interpretan y muestran en una zona concreta del editor.

Se podrán crear nuevas etiquetas pero por defecto se usarán la habituales:

- TODO: Tiene prioridad normal y se utilizará para acciones futuras.
- FIXME: Tiene prioridad alta. No debería usarse para la realización de commits.

**Ejemplo**

/*TODO Comentario que aparecerá marcada como algo para hacer */

=== Sentido común

Sigue el sentido común y no hagas dos veces lo mismo. Esta norma se puede aplicar tanto a nivel de reutilización de código como a nivel de integración.

Si se encuentra o se desarrolla código que puede ser potencialmente reutilizable, se deberá crear un método, clase o módulo con esa funcionalidad. Deberá ser lo más general posible para permitir su reutilización en otros apartados.

El uso de módulos o funcionalidades externas está permitido, pero se deberá documentar la idoneidad del mismo justificando el beneficio de su utilización.

=== Códigos pequeños

Los métodos o algoritmos deberán estar bien modularizados para permitir su mantenimiento. Un buen método no debería tener más de 60 líneas de código sin contar comentarios ni líneas vacías.

== Control del código

El control de código es una cuestión vital para el correcto desarrollo del proyecto. En equipos de desarrollo con muchas personas trabajando en paralelo, el control de versiones permite sincronizarse para que todos l@s integrantes trabajen con la misma versión.

=== Commit (Confirmar)

Intenta hacer ciclos de trabajo cortos. Es preferible hacer muchos commit pequeños que uno con muchos cambios.

Poner un comentario adecuado a una confirmación facilita el entendimiento por l@s integrantes del equipo.

No mantengas muchas confirmaciones sin la correspondiente subida o inserción en el repositorio.

=== Push (Subir o insertar)

Solo se deberán subir códigos funcionales. No tiene porqué corregir el problema para el que hizo el cambio, pero al menos deberá compilar o ejecutar sin errores.

RECUERDA: El control de versiones no es un mecanismo de copia de seguridad. NUNCA subas nada que no esté terminado.

=== Fetch y Pull (Buscar e Incorporar cambios)

Antes de modificar un fichero se deberá comprobar si no existe una versión más reciente del mismo. Esto evitará la necesidada de incorporar cambios.

Si nuestra versión modificada difiere de la versión disponible en el repositorio deberemos realizar un trabajo de incorporación de cambios. En la medida de lo posible deberemos mantener los cambios subidos previamente y analizar si nuestros cambios afecta o son afectados por dichos cambios. En caso de duda se deberá comunicar al autor o autora del último cambio para intentar minimizar el impacto de la mezcla.

=== Branches y Tag (Ramas y etiquetas)

Existirá una rama de desarrolla en la que realizarán todos los trabajos. Habrá un encargado o una encargada (a definir por el grupo) que será el o la responsable de refundir esa rama en la rama principal.

Solo se podrán crear nuevas ramas para realizar trabajos paralelos y consensuado por la mayoría de l@s integrantes del grupo.

== Test

Los pruebas o test tiene como objetivo anticiparse a los fallos de nuestros desarrollos. Aunque no siempre es fácil su realización, deberemos intentar generar al menos test unitarios para nuestros métodos. 

El objetivo final es el disponer de un sistema de integración continua que nos facilite la vida a la hora de publicar nuestro proyecto.
