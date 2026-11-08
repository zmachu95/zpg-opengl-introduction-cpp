import bpy
import mathutils
import os

def export_selected_to_vbo_raw(output_filepath):
    # 1. Kontrola, zda je vybraný nějaký objekt
    obj = bpy.context.active_object
    if obj is None or obj.type != 'MESH':
        print("CHYBA: Vyberte v Blenderu 3D model (Mesh)!")
        return

    print(f"Zpracovávám objekt: {obj.name}")

    # 2. Vytvoření kopie meshe se všemi aplikovanými modifikátory a transformacemi
    dg = bpy.context.evaluated_depsgraph_get()
    obj_eval = obj.evaluated_get(dg)
    mesh = obj_eval.to_mesh()

    # 3. Získání světové matice objektu (převod do World Space)
    world_matrix = obj.matrix_world

    raw_vertices = []
    positions = []

    # Pomocná smyčka pro zjištění Bounding Boxu ve světových souřadnicích (pro normalizaci)
    for poly in mesh.polygons:
        for loop_idx in poly.loop_indices:
            loop = mesh.loops[loop_idx]
            vertex = mesh.vertices[loop.vertex_index]
            world_pos = world_matrix @ vertex.co
            positions.append(world_pos)

    if not positions:
        print("CHYBA: Model neobsahuje žádnou geometrii.")
        return

    # 4. Výpočet Bounding Boxu a normalizačních konstant (rozsah -1.0 až 1.0)
    min_x = min(p.x for p in positions)
    max_x = max(p.x for p in positions)
    min_y = min(p.y for p in positions)
    max_y = max(p.y for p in positions)
    min_z = min(p.z for p in positions)
    max_z = max(p.z for p in positions)

    center_x = (min_x + max_x) / 2.0
    center_y = (min_y + max_y) / 2.0
    center_z = (min_z + max_z) / 2.0

    max_span = max(max_x - min_x, max_y - min_y, max_z - min_z)
    scale = 2.0 / max_span if max_span != 0 else 1.0

    # 5. Kontrola UV mapování
    uv_layer = mesh.uv_layers.active

    # 6. Iterace přes všechny polygony a jejich triangulace (Fan triangulation)
    # Procházíme smyčky (loops), což v Blenderu automaticky řeší unikátní kombinace pozice+normála+UV
    total_vertices = 0
    
    with open(output_filepath, 'w') as out:
        out.write("/**\n")
        out.write(" * @file whiteboard.h \n")
        out.write(" *\n")
        out.write(" * @brief Whiteboard model\n")
        out.write(" *\n")
        out.write(" * @details  Command for rendering\n")
        out.write(" *           glDrawArrays(GL_TRIANGLES, 0, 0);\n")        
        out.write(" *\n")
        out.write(" * @author Martin Nemec\n")
        out.write(" *\n")
        out.write(" * @year 2026\n")
        out.write(" **/\n\n")
        out.write("const float whiteboard[] = {\n")
        out.write("    // [pos.x, pos.y, pos.z]  [norm.x, norm.y, norm.z]  [uv.u, uv.v]\n")

        triangle_count = 0
        for poly in mesh.polygons:
            # Triangulace n-úhelníků na trojúhelníky
            loop_indices = list(poly.loop_indices)
            for i in range(1, len(loop_indices) - 1):
                tris_loops = [loop_indices[0], loop_indices[i], loop_indices[i+1]]
                
                #out.write(f"    // Trojúhelník {triangle_count}\n")
                triangle_count += 1
                
                for idx in tris_loops:
                    loop = mesh.loops[idx]
                    vertex = mesh.vertices[loop.vertex_index]

                    # Pozice ve světovém prostoru + normalizace
                    world_pos = world_matrix @ vertex.co
                    #norm_x = (world_pos.x - center_x) * scale
                    #norm_y = (world_pos.y - center_y) * scale
                    #norm_z = (world_pos.z - center_z) * scale
                    norm_x = world_pos.x
                    norm_y = world_pos.y
                    norm_z = world_pos.z

                    # Normála (převod rotační složky do světového prostoru)
                    world_norm = (world_matrix.to_3x3() @ loop.normal).normalized()

                    # UV souřadnice (Blender má výchozí UV správně, pro 2D textury bez flipu, pro skybox viz minulé upozornění)
                    uv_u = uv_layer.data[idx].uv[0] if uv_layer else 0.0
                    uv_v = uv_layer.data[idx].uv[1] if uv_layer else 0.0

                    out.write(f"    {norm_x:8.5f}f, {norm_y:8.5f}f, {norm_z:8.5f}f,  "
                              f"{world_norm.x:8.5f}f, {world_norm.y:8.5f}f, {world_norm.z:8.5f}f,  "
                              f"{uv_u:8.5f}f, {uv_v:8.5f}f,\n")
                    total_vertices += 1

        out.write("};\n")
        
        # Zapíšeme informaci o počtu vertexů na konec souboru pro glDrawArrays
        out.write(f"\n// Celkový počet vertexů pro glDrawArrays: {total_vertices}\n")

    # Úklid dočasného meshe z paměti Blenderu
    obj_eval.to_mesh_clear()
    
    print(f"Úspěšně exportováno {total_vertices} vertexů do: {output_filepath}")

# --- NASTAVENÍ CESTY PRO EXPORT ---
# Skript uloží textový soubor na vaši plochu (Desktop). Cestu si můžete změnit.
output_path = os.path.expanduser(r"C:\Users\OEM\Desktop\EB408\whiteboard.h")
export_selected_to_vbo_raw(output_path)