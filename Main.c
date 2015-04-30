code Main

  -- OS Class: Project 3
  --
  -- Michael Simpson
  --

-----------------------------  Main  ---------------------------------

  function main ()
      print ("          CS333 Project 3")
      print ("More Classic Synchronization Problems")
      InitializeScheduler ()

      SleepingBarber ()

      ThreadFinish ()
    endFunction



------------------------- Sleeping Barber -----------------------------
enum ENTER, SIT, BEGIN, FINISH, LEAVE, START, END      -- For display purposes
var
    bennys: BarberShop         
    customers: array [20] of Thread = new array of Thread {20 of new Thread }

function SleepingBarber ()
    var
      i: int
      j: int
   
    bennys = new BarberShop
    bennys.Init ()                  -- Initialize the shop
   
    for i = 0 to 19
        customers[i].Init ("C" + i)  --Initialize all customers
        endFor

    for i = 0 to 6
       for j = 0 to 19
           customers[i].Fork ( GoIntoTheShop, i )  -- Each customer tries to get seven haircuts
           endFor
       endFor
    endFunction

function GoIntoTheShop (i: int)

    endFunction

function GetHaircut () -- Args?

    endFunction


class BarberShop
    superclass Object
    fields
        barber: Semaphore           -- Every shop needs a barber
        chairs: Semaphore           -- Where the customers wait
        waiting: int                -- Keep track of how many customers are waiting
        bStatus: int                 -- For display purposes
        cStatus: array[20] of int
    methods
        Init ()                      -- Initialize barber related variables
	OpenUpShop ()                -- Begin the day
        GiveHaircut ()               -- When you get a customer, cut their hair
        PrintStatus ()                    -- Print barber status
  endClass
  behavior BarberShop
    method Init ()
        endMethod

    method OpenUpShop ()
        endMethod

    method GiveHaircut ()
        endMethod

    method PrintStatus ()
        endMethod
    
    endBehavior  
endCode
