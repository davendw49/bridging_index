<p align="center">
    <br>
    <img src="https://big-cheng.com/img/bi.png" width="300"/>
    <br>
<p>

<h4 align="center">
    <p>Package of Bridging Index</p> 
    <p>A node-level metric to evaluate the bridging nature of nodes in networks</p>
</h4>

**Notes**

- Codes for calculating Bridging Index and Ricci-curvature.


## Usage

### 1. As an API

- **Pipeline**

```bash
git clone https://github.com/davendw49/bridging_index.git
cd bridging_index
cp /path/to/your/graph/* graph_data/
cmake .
make
./BridgeIndex
```

- **Notes**

1. *_compare (nodes id mapping files)
2. *_converse (graph with new id)
3. *_bi (Bridging index file with new id)
4. *_ricci (ricci curvature file with new id)
5. *_bi_result (Bridging index file with original id)
6. *_ricci_result (ricci curvature file with original id)

### 2. With your own networks

- **Pre-processing**
    - The data should be in the same format as below, and save as `txt` files.
    ```plain
    source,target,weight,edge_property
    ```

- **Change a few codes**
    - `dateConverse.cpp`:
        - **Line 4** `char2num` (*read the commets in cpp files*)
        - **Line 79** `type` (the name of the dataset folder)
        - **Line 90** `time` (author:19 aff,country:14)
        - **Line 122** `in` (input the edge properties)
        - **Line 142-145** `res.push_back` (input the edge properties)
        - **Line 151-152** length or the data (e.g. for the experiments on scholar network, country:3, aff:4 and author:6)
    - `map.cpp`:
        - **Line 30** `in_g` (input the edge properties)
    - `calculate.cpp`:
        - **Line 14** `type` (same as above)
        - **Line 40** `time` (same as above)
    - `getIDbyNum.cpp`:
        - **Line 6** `type` (same as above)
        - **Line 45** `time` (same as above)

- **Using as API**


## To-do
- [ ] Source code for higher order network property analysis
- [ ] Papers using *Bridging Index* to evaluate the networks
