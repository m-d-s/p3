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
const 
    CHAIRS = 5
var
   customers: array [20] of Thread = new array of Thread {20 of new Thread } 
   barber: Thread = new Thread
   chairs: Semaphore = new Semaphore
   barberAvail: Semaphore = new Semaphore
   lock: Mutex = new Mutex
   waiting: int
function SleepingBarber ()
 var
    i: int
    -- Initialize all variables
    for i = 0 to 19
        customers[i].Init ("C" + i)
      endFor
    barber.Init("Barber")            
    chairs.Init(0)
    barberAvail.Init(0)
    lock.Init()
    waiting = 0
    
    barber.Fork(SetUpShop, -1)                    -- Fork the barber to open the barber shop
    
    for i = 0 to 19
           customers[i].Fork ( MultipleCuts, i )  -- Fork each customer thread to get their haircuts
       endFor
  endFunction

function MultipleCuts (id: int)
    var 
       i: int

    for i = 0 to 9
        GoIntoTheShop (id)            -- Each customer gets ten haircuts
      endFor
  endFunction

function SetUpShop ()
    while true
        chairs.Down ()               -- If no customers are waiting go to sleep
        lock.Lock ()                 
        waiting = waiting - 1        -- Decrement waiting to serve next customer
        barberAvail.Up ()             -- Indicate that barber is busy
        lock.Unlock ()               
        CutHair ()                    -- Begin haircut
    endWhile
  endFunction

function CutHair ()
    var 
      i: int
    lock.Lock ()                   
    Pstart ()                      -- Print haircut start message
    for i = 0 to 99
        currentThread.Yield ()     -- Simulate haircut by looping but also allow other threads to operate by yielding
      endFor
    Pend ()                        -- Print haircut end message
    lock.Unlock ()
  endFunction

function GoIntoTheShop (id: int)
    lock.Lock ()                   
    Penter (id)
    if waiting < CHAIRS              -- See if there is space available to wait
        Psit (id)
        waiting = waiting + 1        -- Increment waiting to let barber know you are there
        chairs.Up ()                 -- Wake the barber
        lock.Unlock ()              
        barberAvail.Down ()          -- Sleep if there is no free barber
        GetHaircut (id)              -- Get your hair did
    else
        Pleave (id)                   
        lock.Unlock ()               -- If there were no seats available, go home
    endIf

  endFunction

function GetHaircut (id: int) 
    var
      i: int
    lock.Lock ()
    Pbegin (id)
    for i = 0 to 99
        currentThread.Yield ()
      endFor
    Pfin (id)
    lock.Unlock ()
  endFunction

function Penter (id: int)
  print("hello")    
  endFunction

function Psit (id: int)
    
  endFunction

function Pbegin (id: int)
    
  endFunction

function Pfin (id: int)
    
  endFunction

function Pleave (id: int)
    
  endFunction

function Pstart ()
    
  endFunction

function Pend ()
    
  endFunction





endCode
