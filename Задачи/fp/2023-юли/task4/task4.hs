cl = [("Kernighan","C"),("Ritchie","C"),("Stroustrup","C++"),("Steele","Scheme"),
      ("Sussman","Scheme"),("Church","Lambda"),("Curry","Lambda")]

votes cand ballots = length $ filter (\ballot -> ballot cand) ballots

election ballots cl = map (\cand@(name, _) -> (name, votes cand ballots)) cl

sortResults [] = []
sortResults ((name, votes):results) = more ++ equal ++ less
                      where more = sortResults $ filter (\(_,v) -> v > votes) results 
                            equal = (name, votes) : filter (\(_,v) -> v == votes) results 
                            less = sortResults $ filter (\(_,v) -> v < votes) results 

selectCouncil max ballots cl = take max (map (\(n,v) -> n) (filter (\(_, v) -> v > length ballots `div` 2) results))
                                where results = sortResults (election ballots cl)
