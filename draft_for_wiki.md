## Basic Structure for Project 3

Classes:

1. Parking area

2. Floor

   1. Special Plot

3. Vehicle

   1. Car
   2. UFO
   3. Spac
   4. Tele

4. Ticket

   

   #### Parking area

   vector of Floor

   #### Floor

   ##### Attribute:

   //vec

   size

   length

   //plot

   2-D array of plot

   row[]

   ##### method

   create_plot(): create a row of plot with specific plot type

   argument:

   plot_type

   *plot_size*

   return value: bool check whether the plot has been created successfully

   true successfully;

   false unsuccessfully;

   

   delete_plot(): delete a row of plot

   return value:

   true successfully;

   false unsuccessfully;

   

   find_plot();

   argument:

   (row,col)

   return value:

   *plot if exist

   NULL if doesn't exist

   

   find_vacant plot()

   argument:

   plot_type

   return value:

   (row,col);

   (-1,-1) if no available plot found

   

   #### Plot

   ##### Attribute:

   plot type

   // 0 normal 1 special

   //color

   r,g,b;

   //vec

   

   size (length,width)

   anchor point:

   vec point to downleft side of the plot

   ##### method:

   bool get_type();

   vec get_size();

   vec get_anchor();

   

   #### ::Special_Plot

   Constructor: type=1;

   ##### Attribute:

   ##### method:

   change_color();

   para:

   last r,g,b;

   return value:

   next r,g,b;???

   

   #### Vehicle

   ##### Attribute:

   type

   size

   float angle;

   anchor

   Ticket in

   Ticket out

   ##### method:

   //animation

   enter();

   exit();

   //ticket

   create_ticket_in()

   create_ticket_out()

   //anchor

   get_anchor()

   move()

   virtual rotate(); //redirect the critical point of all types of vehicle

   //size

   get_size();

   zoom();

   zoom_in();

   zoom_out();

   //type

   get_type();

   #### ::Car

   ##### Attribute:

   //critical points

   

   ##### method:

   #### ::UFO

   ##### Attribute:

   //critical points

   

   ##### method:

   auto_rotate();

   #### ::Teleported

   ##### Attribute:

   size=0;

   //critical point = anchor point

   ##### method:

   instant_enter();

   instant_exit();

   #### ::SpaceCraft

   ##### Attribute:

   ##### method:

   auto_zoom();

   #### Ticket

   ##### Attribute:

   car_type

   arrival time

   

   #### ::TickIn

   ##### Attribute:

   slot (row,col) 

   #### ::TickOut

   ##### Attribute:

   leave_time

   price

   ##### Method:

   get_interval()

   set_price();

​		

​	