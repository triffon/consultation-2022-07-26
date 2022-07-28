data Tree a = EmptyTree | Node {
    value :: a,
    left :: Tree a,
    right :: Tree a
 } deriving (Show, Read)

{- Довършете функцията treeWords:
1. Опишете типа на функцията така, че тя да получава дърво от символи и да връща списък от символни низове.
2. Функцията да връща списък от всички думи, които могат да се образуват по път от корена до някое от листата на дървото. Ако дървото е празно, да се връща празният списък.-}

treeWords :: Tree Char -> [String]
treeWords EmptyTree = []
treeWords (Node v EmptyTree EmptyTree) = [[ v ]]
treeWords (Node v l r) = map (v:) (wl ++ wr)
 where wl = treeWords l
       wr = treeWords r


leaf :: Char -> Tree Char
leaf c = Node c EmptyTree EmptyTree


tree :: Tree Char
tree = Node 'h' (Node 'e' (leaf 'x')  (leaf 'n')) (leaf 'i')

quickSort :: Ord a => [a] -> [a]
quickSort []     = []
quickSort (x:xs) = quickSort lesser ++ [x] ++ quickSort greater
  where
     lesser  = filter (<x ) xs
     greater = filter (>=x) xs
