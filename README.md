# polyomino_integer

run as 
```shell
./bin/GP_mapper number of [repeated builds] [Determinism threshold (=1)] [Run]
```
where run is the Nth run of data.

Populate file with genotypes titled Genotype\_Inputs\_Run\[Run\].txt with one genotype per line.
e.g.

```
0 0 0 1 0 0 0 2
0 0 1 2
1 3 0 0 2 0 0 4
1 3 0 0 0 2 0 4
```
And then the output is in Assembly\_Outputs\_Run\[Run\].txt, with each Phenotype ID (pid) on its own line.

The pid matches the phenotype as detailed in the PhenotypeTable_Run\[Run\].txt file.

The phenotypes can be plotted in vis.py with the \[Run\] and pid tuple, e.g.
```python
plotPhenotype(0,(4,0))
plotPhenotype(0,(2,0))
```
which plots the two examples from above
