code Main

  -- OS Class: Project 3
  --
  -- Michael Simpson
  --

-----------------------------  Main  ---------------------------------

  function main ()
      print ("          CS333 Project 3")
      print ("More Classic Synchronization Problems")
      InitializeSheduler ()

      SleepingBarber ()

      ThreadFinish ()
    endFunction



------------------------- Sleeping Barber -----------------------------
enum ENTER, SIT, BEGIN, FINISH, LEAVE, START, END
var
    bennys: BarberShop
    customers: array[20] of Thread = new array of Thread { 5 of new Thread }

function SeepingBarber ()
    var
      i: int
      j: int
   
    bennys = new BarberShop
    bennys.Init ()
   
    for i = 0 to 19
        customer[i].Init ("C" + i)  --Initialize all customers
        endFor

    for i = 0 to 6
       for j = 0 to 19
           customer[i].Fork ( checkTheShop, i )  -- Each customer tries to get seven haircuts
           endFor
       endFor
    endFunction


class BarberShop
    superclass Object
    fields
        barber: semaphore           -- Every shop needs a barber
        chairs: semaphore           -- Where the customers wait
        waiting: int                -- Keep track of how many customers are waiting
        status: int                 -- For display purposes
 
    methods
        Init ()                      -- Initialize barber related variables
	OpenUpShop ()                -- Begin the day
        GiveHaircut ()               -- When you get a customer, cut their hair
        BPrint ()                    -- Print barber status
    endClass


function checkTheShop (i: int)

    endFunction

function getHaircut () -- Args?

    endFunction

function CPrint()

    endFunction

endCode
