# mol2msi

Convert Ketcher generated .mol format chemical structure file to .msi format. Written in C.

## Mechanism

The third line of the Ketcher generated .mol file tells the number of atoms and bonds by the first and second integer.

```
  5  4  0  0  0  0            999 V2000
```

Next _n = number of atoms_ lines describing the (x, y, z) coordinates and element symbol of the atoms. E.g.

```
    (x)       (y)       (z)    Symbol /* This line does not exist */
    0.0000    0.0000    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0
    0.8660   -0.5000    0.0000 C   0  0  0  0  0  0  0  0  0  0  0  0
   -0.8660   -0.5000    0.0000 H   0  0  0  0  0  0  0  0  0  0  0  0
    0.0000    1.0000    0.0000 O   0  0  0  0  0  0  0  0  0  0  0  0
    1.7321    0.0000    0.0000 O   0  0  0  0  0  0  0  0  0  0  0  0
```

Followed by _n = number of bonds_ lines describing the bonding atoms and type of bonds.

```
(atom1) (atom2) (bond type) /* This line does not exist */
     1       2            1  0  0  0  0
     1       3            1  0  0  0  0
     1       4            2  0  0  0  0
     2       5            2  0  0  0  0
```

So we can extract these essential information about atoms and bonds. (parse_mol.c)
To convert to .msi format, we need to format the atoms and bonds into the corresponding formats.

A single atom is described in .msi file like this:

```
  (2 Atom
    (A C ACL "2 C")
    (A C Label "C")
    (A D XYZ (0.000000 0.000000 0.000000))
    (A I Id 2)
  )
```

The 2 in `2 Atom` is the id of the item in .msi file. 1 is occupied by `1 Model`, which is the head of the .msi file block structures.
The next four lines are objects of the atom block.

Object:

- ACL: Tells the id of atom and element symbol.
- Label: Element Symbol.
- XYZ: Absolute cartesian coordinates.
- Id: Id for reference.

Type notation:

- C = char
- D = double
- I = int
- O = object

Bonds are put after atoms.

```
  (10 Bond
    (A O Atom1 3)
    (A O Atom2 6)
    (A I Type 2)
  )
```

The `Atom1` `Atom2` refers to the ids of bonding atoms. `Type` can be ignored if it is 1. It tells whether it is a single bond, double bond or triple bond.
