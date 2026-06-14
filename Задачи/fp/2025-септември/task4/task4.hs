import Data.List (nub)
work = [ ("X","A",40), ("X","B",30), ("Y","A",60), ("Y","C",50), ("Z","B",20), ("Z","C",20) ]

empAssignments emp = filter (\(е,_,_) -> е == emp) work

totalLoad emp = sum (map (\(_,_,l) -> l) (empAssignments emp))

overloaded = filter (\(e,_,_) -> totalLoad e > 100) work

overloaded2 = nub (map (\(e,_,_) -> e) (filter (\(e,_,_) -> totalLoad e > 100) work))

minLoad (_, project, load) = load <= minimum [ l | (_, p, l) <- work, p == project]

optimize = map (\r@(emp,project, load) -> let t = totalLoad emp in 
                                         if (t < 100 && minLoad r && length (filter minLoad (empAssignments emp)) == 1)
                                         then (emp, project, load + (100 - t))
                                         else r) work
main = do
  print (empAssignments "X")
  print (totalLoad "X")
  print (overloaded)
  print (minLoad ("Z","C",20))
  print (optimize)