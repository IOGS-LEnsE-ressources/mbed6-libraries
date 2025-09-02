def pbm_to_c_array(pbm_path, array_name="image_data"):
    with open(pbm_path, "rb") as f:
        # Lire l'en-tête PBM (P4 = binaire)
        header = f.readline()
        if header.strip() != b"P4":
            raise ValueError("Le fichier n'est pas un PBM binaire (P4)")

        # Ignorer les commentaires éventuels
        dimensions = b""
        while not dimensions:
            line = f.readline()
            if not line.startswith(b"#"):
                dimensions = line.strip()

        width, height = map(int, dimensions.split())

        # Calcul de la taille en octets par ligne (alignée sur 8 bits)
        row_bytes = (width + 7) // 8

        # Lecture des données binaires de l'image
        image_data = f.read(row_bytes * height)

    # Génération du tableau C
    output = []
    output.append(f"#ifndef __IMAGE_{name}_H")
    output.append(f"#define __IMAGE_{name}_H")

    output.append(f"__IO const uint8_t {array_name}[] = {{")
    
    line = "    "
    for i, byte in enumerate(image_data):
        line += f"0x{byte:02X}, "
        if (i + 1) % 12 == 0:  # saut de ligne toutes les 12 valeurs
            output.append(line)
            line = "    "
    if line.strip():
        output.append(line)
    output.append("};")
    
    # Informations sur la taille
    output.append(f"\n// Image: {width} x {height} pixels")
    output.append(f"// Taille du tableau: {len(image_data)} octets\n")
    output.append(f"\n#endif\n")
    
    return "\n".join(output)


# Exemple d'utilisation
if __name__ == "__main__":
    name = input('Name of the picture ?')
    pbm_file = f"Images/{name}.pbm"  
    c_array_code = pbm_to_c_array(pbm_file, array_name=f"im{name}")

    with open(f"Inc/image_output_{name}.h", "w") as f:
        f.write(c_array_code)

    print(f"Tableau C généré dans 'image_output_{name}.h'")