import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
 
# Make a data frame
df=pd.DataFrame({'x': ['Native', 'One VM', 'Two VMs', 'Three VMs', 'Four VMs'], 
                 'D-Cache miss': [192, 10167, 492228, 897950, 3903672],
                 'I-Cache miss': [651, 712,  155134,  617441, 3788338]})
 
 
# create a color palette
palette = plt.get_cmap('Set1')
 
# multiple line plot
num=0
for column in df.drop('x', axis=1):
    num+=1
    plt.plot(df['x'], df[column], marker='o', color=palette(num), linewidth=1, alpha=0.9, label=column)
 

# Text on the top of each barplot
for i in range(len(df['x'])):
    if i<3:
        plt.text(x = i+0.05, y = df['D-Cache miss'][i]+50000, s = df['D-Cache miss'][i], size = 7)
        plt.text(x = i+0.05, y = df['I-Cache miss'][i]-80000, s = df['I-Cache miss'][i], size = 7)
    else:
        plt.text(x = i+0.05, y = df['D-Cache miss'][i], s = df['D-Cache miss'][i], size = 7)        
        plt.text(x = i+0.05, y = df['I-Cache miss'][i], s = df['I-Cache miss'][i], size = 7)


# Add legend
plt.legend()
 
# Add titles
#plt.title("Data and Instruction Cache Misses", loc='Center', fontsize=12, fontweight=0)
plt.xlabel("System Configuration")
plt.ylabel("Number of Cache Misses")

plt.savefig('cache_misses.eps', format='eps')
#plt.show()