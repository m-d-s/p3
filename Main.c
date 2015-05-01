code Main

  -- OS Class: Project 3
  --
  -- Michael Simpson
  --

-----------------------------  Main  ---------------------------------

  function main ()
      print ("          CS333 Project 3\n")
      print ("More Classic Synchronization Problems\n")
      InitializeScheduler ()

      SleepingBarber ()

      ThreadFinish ()
    endFunction



------------------------- Sleeping Barber -----------------------------
enum ENTER, SIT, LEAVE, BEGIN, FINISH, START, END, DEFAULT
const 
    CHAIRS = 5
var
   customers: array [20] of Thread = new array of Thread {20 of new Thread } 
   barber: Thread = new Thread
   chairs: Semaphore = new Semaphore
   barberAvail: Semaphore = new Semaphore
   lock: Mutex = new Mutex
   waiting: int
   status: array[21] of int = new array of int {21 of DEFAULT}
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
     print("   chairs     B 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n")
 
    barber.Fork(SetUpShop, 0)                    -- Fork the barber to open the barber shop
       for i = 0 to 19
           customers[i].Fork ( MultipleCuts, i+1 )  -- Fork each customer thread to get their haircuts
       endFor
  endFunction

function MultipleCuts (id: int)
    var 
       i: int

    for i = 0 to 9
        GoIntoTheShop (id)            -- Each customer gets ten haircuts
      endFor
  endFunction

function SetUpShop (id: int)
    while true
        chairs.Down ()               -- If no customers are waiting go to sleep
        lock.Lock ()                 
        waiting = waiting - 1        -- Decrement waiting to serve next customer
        barberAvail.Up ()             -- Indicate that barber is busy
        lock.Unlock ()               
        CutHair (id)                    -- Begin haircut
    endWhile
  endFunction

function CutHair (id: int)
    var 
      i: int
    lock.Lock ()
    status[id] = START                   
    Print (id)                      -- Print haircut start message
    for i = 0 to 99
        currentThread.Yield ()     -- Simulate haircut by looping but also allow other threads to operate by yielding
      endFor
    status[id] = END
    Print (id)                        -- Print haircut end message
    lock.Unlock ()
  endFunction

function GoIntoTheShop (id: int)
    lock.Lock () 
    status[id] = ENTER                  
    Print (id)
    if waiting < CHAIRS              -- See if there is space available to wait
        status[id] = SIT
        Print (id)
        waiting = waiting + 1        -- Increment waiting to let barber know you are there
        chairs.Up ()                 -- Wake the barber
        lock.Unlock ()              
        barberAvail.Down ()          -- Sleep if there is no free barber
        GetHaircut (id)              -- Get your hair did
    else
        status[id] = LEAVE
        Print (id)                   
        lock.Unlock ()               -- If there were no seats available, go home
    endIf

  endFunction

function GetHaircut (id: int) 
    var
      i: int
    lock.Lock ()
    status[id] = BEGIN
    Print (id)
    for i = 0 to 99
        currentThread.Yield ()
      endFor
    status[id] = FINISH
    Print (id)
    lock.Unlock ()
  endFunction

function Print (id: int)
    var
      i: int
      buff: int
    PrintChairs(id)
    buff = ((id*2)+1)   
    for i = 0 to buff 
        print(" ")
        --if i > 9
         --   print(" ")
        --endIf
    endFor
    switch status[id]
        case ENTER:
            print("E")
          break
        case SIT:
            print("S")
          break
        case LEAVE:
            print("L")
          break
        case START:
            print("I")
          break
        case END:
            print("C")
          break
        case BEGIN:
            print("B")
          break
        case FINISH:
            print("F")
          break
        default:          
      endSwitch
      nl ()

  endFunction

function PrintChairs(id: int)
    var
      i: int

    for i = 0 to CHAIRS
	if i > waiting
	    print("_ ")
	else
	    print("X ")
	endIf
     endFor              
  endFunction

endCode
