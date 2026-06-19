dom = [0, 1, 2]

eqFn f g = all (\x -> f x == g x) dom

memFn f fs = any (\g -> eqFn f g) fs

checkRan f = all (\new_x -> elem new_x dom) (map f dom)

isMonoid fs = all checkRan fs &&
              memFn id fs &&
              all (\f -> all (\g -> memFn (f . g) fs) fs) fs
