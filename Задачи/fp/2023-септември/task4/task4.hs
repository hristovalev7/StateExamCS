data Expr = N Integer | X | F Char Expr Expr

exprs = [F '-' (F '*' X X) (N 1), F '+' (F '*' X (N 2)) (N 3),
         F '*' (F '*' X X) (F '+' X (N 2)), F '+' (F '^' X (N 3)) (N 1)]

lib = [('+',(+)),('-',(-)),('*',(*))]

correct lib (F f l r) = elem f (map (\(x,y) -> x) lib) && correct lib l && correct lib r
correct _   (N _)     = True
correct _   X         = True

calc lib (N n) _ = n
calc lib X     x = x 
calc lib (F c l r) x = (head [f | (fc, f) <- lib, fc == c]) (calc lib l x) (calc lib r x)

check a b lib f expr = all (\x -> correct lib expr && calc lib expr x == f x) [a..b]

score a b lib fs exprs = fromIntegral (length (filter id (zipWith (check a b lib) fs exprs)))
                         / fromIntegral (length fs)

main :: IO ()
main = do
  print (score (-10) 10 lib [\x -> x^2-1, \x -> x*3+2, \x -> x^3+2*x^2, \x -> x^3+1] exprs)
