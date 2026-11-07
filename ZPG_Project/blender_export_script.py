# Script for exporting objects from Blender to vertex *.h files
# Created by Google Gemini

import os

def parse_and_normalize_obj_no_ebo(input_path, output_path, array_name):
    positions = []
    normals = []
    uvs = []
    face_elements = []
    
    if not os.path.exists(input_path):
        print(f"Chyba: Soubor '{input_path}' neexistuje.")
        return

    print("Načítám a zpracovávám OBJ soubor...")
    with open(input_path, 'r') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
                
            tokens = line.split()
            prefix = tokens[0]
            
            if prefix == 'v':
                positions.append([float(tokens[1]), float(tokens[2]), float(tokens[3])])
            elif prefix == 'vn':
                normals.append([float(tokens[1]), float(tokens[2]), float(tokens[3])])
            elif prefix == 'vt':
                uvs.append([float(tokens[1]), float(tokens[2])])
            elif prefix == 'f':
                face_vertices = []
                for token in tokens[1:]:
                    parts = token.split('/')
                    p_idx = int(parts[0]) - 1 if parts[0] else 0
                    t_idx = int(parts[1]) - 1 if (len(parts) > 1 and parts[1]) else -1
                    n_idx = int(parts[2]) - 1 if (len(parts) > 2 and parts[2]) else -1
                    face_vertices.append((p_idx, n_idx, t_idx))
                
                # Automatická triangulace přímo do sekvenčního seznamu
                for i in range(1, len(face_vertices) - 1):
                    face_elements.append(face_vertices[0])
                    face_elements.append(face_vertices[i])
                    face_elements.append(face_vertices[i+1])

    if not positions:
        print("Chyba: V souboru nebyla nalezena žádná geometrie.")
        return

    print("Normalizuji souřadnice vrcholů do rozsahu [-1.0, 1.0]...")
    # Nalezení Bounding Boxu pro normalizaci pozic
    min_x = min(p[0] for p in positions)
    max_x = max(p[0] for p in positions)
    min_y = min(p[1] for p in positions)
    max_y = max(p[1] for p in positions)
    min_z = min(p[2] for p in positions)
    max_z = max(p[2] for p in positions)
    
    center_x = (min_x + max_x) / 2.0
    center_y = (min_y + max_y) / 2.0
    center_z = (min_z + max_z) / 2.0
    
    max_span = max(max_x - min_x, max_y - min_y, max_z - min_z)
    scale = 2.0 / max_span if max_span != 0 else 1.0

    print(f"Ukládám rozbalená data do: {output_path}")
    with open(output_path, 'w') as out:
        out.write("// Vygenerováno automatickým skriptem pro OpenGL (Pouze sekvenční VBO)\n")
        out.write(f"// Celkem vertexů pro glDrawArrays: {len(face_elements)}\n\n")
        
        out.write(f"float {array_name}[] = " + "{\n")
        out.write("    // [pos.x, pos.y, pos.z]  [norm.x, norm.y, norm.z]  [uv.u, uv.v]\n")
        
        # Zapisujeme vertex po vertexu tak, jak jdou sekvenčně v trojúhelnících za sebou
        for i, vert in enumerate(face_elements):
            p_idx, n_idx, t_idx = vert
            
            # 1. Normalizace pozice
            pos = positions[p_idx]
            norm_x = (pos[0] - center_x) * scale
            norm_y = (pos[1] - center_y) * scale
            norm_z = (pos[2] - center_z) * scale
            
            # 2. Načtení normály
            norm = normals[n_idx] if n_idx != -1 else [0.0, 0.0, 0.0]
            
            # 3. Načtení UV souřadnic
            uv = uvs[t_idx] if t_idx != -1 else [0.0, 0.0]
            
            # Přidáme vizuální oddělovač po každém trojúhelníku (3 vrcholy) pro lepší čitelnost
            comment = f" // Začátek trojúhelníku {i // 3}" if i % 3 == 0 else ""
            
            out.write(f"    {norm_x:8.5f}f, {norm_y:8.5f}f, {norm_z:8.5f}f,  "
                      f"{norm[0]:8.5f}f, {norm[1]:8.5f}f, {norm[2]:8.5f}f,  "
                      f"{uv[0]:8.5f}f, {uv[1]:8.5f}f,{comment}\n")
                      
        out.write("};\n")

    print("Hotovo!")

if __name__ == "__main__":
    AKTUALNI_SLOZKA = r"C:\Users\OEM\Desktop\shrekFiona"
    VSTUPNI_OBJ = f"{AKTUALNI_SLOZKA}\\toiled.obj" 
    VYSTUPNI_TXT = f"{AKTUALNI_SLOZKA}\\toiled.h"
    ARRAY_NAME = "toiletVertices"
    
    parse_and_normalize_obj_no_ebo(VSTUPNI_OBJ, VYSTUPNI_TXT, ARRAY_NAME)
