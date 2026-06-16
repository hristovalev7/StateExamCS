length2 [] = 0
length2 (x : xs) = 1 + length2 xs

map2 _ [] = []
map2 f (x : xs) = f x : map2 f xs

filter2 _ [] = []
filter2 p (x : xs)
  | p x = x : filter2 p xs
  | otherwise = filter2 p xs

foldl2 _ nv [] = nv
foldl2 op nv (x : xs) = foldl2 op (nv `op` x) xs

foldr2 _ nv [] = nv
foldr2 op nv (x : xs) = x `op` foldr2 op nv xs
