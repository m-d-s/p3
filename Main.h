header Main

  uses System, Thread, Synch

  functions
    main ()
    SleepingBarber ()
    MultipleCuts (id: int)
    SetUpShop (id: int)
    CutHair (id: int)
    GoIntoTheShop (id: int)
    GetHaircut (id: int)
    Print (id: int)
    PrintChairs ()  

    GamingParlor ()
    Play (p: int)

  class Monitor
    superclass Object
    fields
      numDiceAvail: int
      lineForDice: int
      monLock: Mutex                      
      monCons: array [2] of Condition      
    methods
      Init ()
      Request (p: int)
      Return (p: int)
      Print (str: String, count: int)    
    endClass

endHeader
