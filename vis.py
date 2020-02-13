from polyomino_core.scripts.polyomino_visuals import VisualiseSingleShape

def plotPhenotype(run, pid,fpath=''):
    phenotypes = sorted([[int(i) for i in line.split()] for line in open(f'{fpath}PhenotypeTable_Run{run}.txt')],key=lambda z: z[0])
    phenotype_table = {tuple(px[:2]): tuple(px[2:]) for px in phenotypes}

    VisualiseSingleShape(phenotype_table[pid])
