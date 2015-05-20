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
      --GamingParlor ()
      ThreadFinish ()
    endFunction



------------------------- Sleeping Barber -----------------------------
enum ENTER, SIT, LEAVE, BEGIN, FINISH, START, END, DEFAULT
const 
    CHAIRS = 5
var
   threads: array [21] of Thread = new array of Thread {21 of new Thread } 
   customers: Semaphore = new Semaphore
   barber: Semaphore = new Semaphore
   lock: Mutex = new Mutex
   waiting: int
   status: array[21] of int = new array of int {21 of DEFAULT}

function SleepingBarber ()
var
    i: int
   
    --Initialize all variables
    for i = 0 to 20
        threads[i].Init ("T" + i)
      endFor
    customers.Init(0)
    barber.Init(0)
    lock.Init()
    waiting = 0    

    print("   chairs    B 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n")
    print("_________________________________________________________________\n")
    threads[0].Fork(SetUpShop, 0)                    -- Fork the barber to open the barber shop
       for i = 1 to 20
           threads[i].Fork ( MultipleCuts, i )       -- Fork each customer thread to get their haircuts
       endFor
  endFunction

function MultipleCuts (id: int)
    var 
       i: int
       j: int
    for i = 0 to 9
        for j = 0 to id *id * 1000    -- Wait to keep all threads from running at the same time
          endFor     
        GoIntoTheShop (id)            -- Each customer gets ten haircuts
      endFor
  endFunction

function SetUpShop (id: int)
    while true
        customers.Down ()             -- If no customers are waiting go to sleep
        lock.Lock ()                 
        waiting = waiting - 1         -- Decrement waiting to serve next customer
        barber.Up ()                  -- Wake a sleeping customer thread
        lock.Unlock ()               
        CutHair (id)                  -- Begin haircut
    endWhile
  endFunction

function CutHair (id: int)
    var 
      i: int
    lock.Lock ()
    status[id] = START                   
    Print (id)                        -- Print haircut start message
    lock.Unlock ()
    for i = 0 to 99
        currentThread.Yield ()        -- Simulate haircut by looping but also allow other threads to operate by yielding
      endFor
    lock.Lock ()
    status[id] = END
    Print (id)                        -- Print haircut end message
    lock.Unlock ()
  endFunction

function GoIntoTheShop (id: int)
    lock.Lock () 
    status[id] = ENTER                  
    Print (id)
    if waiting < CHAIRS              -- See if there is space available to wait
        waiting = waiting + 1        -- Increment waiting to let barber know you are there
        status[id] = SIT
        Print (id)                   -- Print sitting message
        customers.Up ()              -- Wake the barber
        lock.Unlock ()             
        barber.Down ()               -- Sleep if there is no free barber
        GetHaircut (id)              -- Get your hair did
    else
        status[id] = LEAVE           -- No available seats, customer must leave
        Print (id)                   -- Print leaving message
        lock.Unlock ()               -- If there were no seats available, go home
    endIf

  endFunction

function GetHaircut (id: int) 
    var
      i: int
    lock.Lock ()
    status[id] = BEGIN               -- Begin the haircut 
    Print (id)                       -- Print begin message
    lock.Unlock ()
    for i = 0 to 74
        currentThread.Yield ()       -- simulate getting the haircut and let other threads run
      endFor
    lock.Lock ()
    status[id] = FINISH              -- Finish the haircut
    Print (id)                       -- Print finish message
    lock.Unlock ()

    for i = 0 to 49
        currentThread.Yield ()       -- simulate paying for the haircut
      endFor

    lock.Lock ()
    status[id] = LEAVE               -- Leave the shop
    Print (id)                       -- Print leave message
    lock.Unlock ()
  endFunction

function Print (id: int)             -- Print the chair and customer status
    var
      i: int
      buff: int
    PrintChairs()
    buff = (id*2)                    -- Spacing buffer to generate column style output

    if id > 9                        -- Calculating spacing offsets for threads w/ 2 digit id
        if id > 19                          
            buff = buff + 10
        else
            buff = buff + (id % 10)
        endIf
    endIf

    for i = 0 to buff                -- Print the spacing offset
        print(" ")
    endFor

    switch status[id]                -- Print the threads current status
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
            print("I")              -- Only used by barber "Init"
          break
        case END: 
            print("C")              -- Only used by barber "Complete"
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

function PrintChairs()               -- Print the number of waiting customers
    var
      i: int

    for i = 1 to CHAIRS
	if i > waiting
	    print("_ ")
	else
	    print("X ")
	endIf
     endFor 
    print ("  ")             
  endFunction


------------------------- Gaming Parlor -----------------------------


  enum PICTIONARY, MONOPOLY, DUMMY, BACKGAMMON, RISK
  var
    frontDesk: Monitor = new Monitor
    gamers: array [8] of Thread = new array of Thread {8 of new Thread }

  function GamingParlor ()

      frontDesk.Init ()
      
      gamers[0].Init("A")
      gamers[0].Fork (Play, BACKGAMMON)
  
      gamers[1].Init("B")
      gamers[1].Fork (Play, BACKGAMMON)

      gamers[2].Init("C")
      gamers[2].Fork (Play, RISK)
  
      gamers[3].Init("D")
      gamers[3].Fork (Play, RISK)

      gamers[4].Init("E")
      gamers[4].Fork (Play, MONOPOLY)
  
      gamers[5].Init("F")
      gamers[5].Fork (Play, MONOPOLY)

      gamers[6].Init("G")
      gamers[6].Fork (Play, PICTIONARY)
  
      gamers[7].Init("H")
      gamers[7].Fork (Play, PICTIONARY)


     endFunction

  function Play (p: int)
      var
        i: int
        j: int
      for i = 0 to 5
          frontDesk.Request(p)              -- Aquire the dice 
          for j = 0 to 100
              currentThread.Yield()         -- Simulate gameplay
            endFor
          frontDesk.Return(p)               -- Return the dice
      endFor
    endFunction

  behavior Monitor

    method Init ()
       var
         i: int
       numDiceAvail = 8                     -- To begin there are eight dice available
       lineForDice = 0                      -- and there is no one in line for the dice
       
       monLock = new Mutex
       monLock.Init()                       -- Initialize all other monitor variables
       monCons = new array[2] of Condition {2 of new Condition}
       for i = 0 to 1
         monCons[i].Init()
       endFor 
     endMethod

    -- A group tries to reqest dice for their game
    method Request (p: int)                 
        monLock.Lock()                      -- Lock mutex to avoid race conditions
        self.Print("Requests", p)           -- Print a status that shows the group is requesting p dice
 
       if lineForDice > 0                   -- Check to see if anyone else is waiting in line
          monCons[0].Wait(&monLock)        -- This condition ensures fairness in dice dispersal
       endIf                               
       
       lineForDice = (lineForDice + 1)        
    
       while numDiceAvail < p               -- Must loop here while waiting for dice due to Mesa semantics
          monCons[1].Wait(&monLock)
       endWhile
       
       numDiceAvail = (numDiceAvail - p)    -- Now there are enough dice, aquire the dice for your game 
       self.Print("Aquires", p)             -- Print a status that shows your group got their dice
       lineForDice = (lineForDice - 1)
       monCons[0].Signal(&monLock)          -- Signal next group in line prior to leaving critical section
       monLock.Unlock()                     -- Release the mutex and go play
     endMethod

    -- A group is finished playing an needs to return their dice
    method Return (p: int)
       monLock.Lock()                        -- Lock mutex to avoid race conditions
       self.Print("Releases", p)             -- Display message to show you are returning dice
       numDiceAvail = (numDiceAvail + p)     -- Add the dice back to the pool
       monCons[1].Signal(&monLock)
       monLock.Unlock()                         
     endMethod

       method Print (str: String, count: int)
        --
        -- This method prints the current thread's name and the arguments.
        -- It also prints the current number of dice available.
        --
        print (currentThread.name)
        print (" ")
        print (str)
        print (" ")
        printInt (count)
        nl ()
        print ("------------------------------Number of dice now avail = ")
        printInt (numDiceAvail)
        nl ()
      endMethod
  endBehavior

endCode
