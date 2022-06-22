#pragma once

#include <cstdint>
#include "../../valve.h"

using quaternion = float[4];
using radian_euler = float[3];

#define MAX_QPATH  260

#define BONE_CALCULATE_MASK             0x1F
#define BONE_PHYSICALLY_SIMULATED       0x01    // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL         0x02    // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL          0x04    // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE        0x08    // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER      0x10    // bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK                  0x0007FF00
#define BONE_USED_BY_ANYTHING           0x000FFF00
#define BONE_USED_BY_HITBOX             0x00000100    // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT         0x00000200    // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK        0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0        0x00000400    // bone (or child) is used by the toplevel model via skinned vertex

#define BONE_USED_BY_VERTEX_LOD1        0x00000800
#define BONE_USED_BY_VERTEX_LOD2        0x00001000
#define BONE_USED_BY_VERTEX_LOD3        0x00002000
#define BONE_USED_BY_VERTEX_LOD4        0x00004000
#define BONE_USED_BY_VERTEX_LOD5        0x00008000
#define BONE_USED_BY_VERTEX_LOD6        0x00010000
#define BONE_USED_BY_VERTEX_LOD7        0x00020000
#define BONE_USED_BY_BONE_MERGE         0x00040000    // bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8
#define MAXSTUDIOBONES		256		// total bones actually used

#define BONE_TYPE_MASK                  0x00F00000
#define BONE_FIXED_ALIGNMENT            0x00100000    // bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS          0x00200000    // Vector48
#define BONE_HAS_SAVEFRAME_ROT64        0x00400000    // Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32        0x00800000    // Quaternion32

#define HITGROUP_GENERIC 0
#define HITGROUP_HEAD 1
#define HITGROUP_CHEST 2
#define HITGROUP_STOMACH 3
#define HITGROUP_LEFTARM 4
#define HITGROUP_RIGHTARM 5
#define HITGROUP_LEFTLEG 6
#define HITGROUP_RIGHTLEG 7
#define HITGROUP_GEAR 10

enum hitboxes {
	hitbox_head,
	hitbox_neck,
	hitbox_pelvis,
	hitbox_stomach,
	hitbox_lower_chest,
	hitbox_chest,
	hitbox_upper_chest,
	hitbox_right_thigh,
	hitbox_left_thigh,
	hitbox_right_calf,
	hitbox_left_calf,
	hitbox_right_foot,
	hitbox_left_foot,
	hitbox_right_hand,
	hitbox_left_hand,
	hitbox_right_upper_arm,
	hitbox_right_forearm,
	hitbox_left_upper_arm,
	hitbox_left_forearm,
	hitbox_max
};

using mdl_handle_t = unsigned short;

struct mstudiobone_t {
	int m_name_index;
	char* const pszName(void) const { return ((char*)this) + m_name_index; }
	int m_parent;
	int m_bone_controller[6];
	vec3_t m_pos;
	quaternion m_quat;
	radian_euler m_rot;

	vec3_t m_pos_scale;
	vec3_t m_rot_scale;

	matrix_t m_pose_to_bone;
	quaternion m_alignment;
	int m_flags;
	int m_proc_type;
	int m_proc_index;
	mutable int m_physics_bone;
	int m_surface_prop_idx;

	int m_contents;
	int m_surface_prop_lookup;
	int m_pad01[7];

	char* psz_surface_prop(void) const { return (char*)(this + m_surface_prop_idx); }
	int get_surface_prop(void) const { return m_surface_prop_lookup; }

	mstudiobone_t() {
	}

private:
	mstudiobone_t(const mstudiobone_t& vOther);
};


struct mstudiobbox_t {
	int m_bone;
	int m_group;
	vec3_t m_mins;
	vec3_t m_maxs;
	int m_hitbox_name_index;
	vec3_t m_rotation;
	float m_radius;
	int pad2[4];

	const char* get_name() {
		if (!m_hitbox_name_index)
			return nullptr;

		return reinterpret_cast<const char*>(reinterpret_cast<uint8_t*>(this) + m_hitbox_name_index);
	}
};

struct mstudiohitboxset_t {
	int m_name_index;
	int m_num_hitboxes;
	int m_hitbox_index;

	const char* get_name() {
		if (!m_name_index) 
			return nullptr;

		return reinterpret_cast<const char*>(reinterpret_cast<uint8_t*>(this) + m_name_index);
	}

	mstudiobbox_t* get_hitbox(int i) {
		if (i > m_num_hitboxes)
			return nullptr;

		return reinterpret_cast<mstudiobbox_t*>(reinterpret_cast<uint8_t*>(this) + m_hitbox_index) + i;
	}
};

struct model_t {
	char pad0[4];
	char m_name[260];
	int	m_load_flags;
	int	m_server_count;
	int	m_type;
	int m_flags;
	vec3_t m_mins;
	vec3_t m_maxs;
	float m_radius;
	void* m_key_values;
	char pad1[24];
};

class studiohdr_t {
public:
	__int32 m_id; 
	__int32 m_version;
	long m_checksum;
	char m_sz_name[64];
	__int32 m_length;
	vec3_t m_eye_pos;
	vec3_t m_illum_pos;
	vec3_t m_hull_min;
	vec3_t m_hull_max;
	vec3_t m_bb_min;
	vec3_t m_bb_max;
	__int32 m_flags;
	__int32 m_num_bones;
	__int32 m_bone_index;
	__int32 m_num_bone_controllers;
	__int32 m_bone_controller_index;
	__int32 m_num_hitbox_sets;
	__int32 m_hitbox_set_index; 
	__int32 m_num_local_anim;
	__int32 m_local_anim_index;
	__int32 m_num_local_seq;
	__int32 m_local_seq_index;
	__int32 m_activity_list_version;
	__int32 m_events_indexed;
	__int32 m_num_textures;
	__int32 m_texture_index;

	mstudiohitboxset_t* get_hitbox_set(const int i) {
		if (i > m_num_hitbox_sets) return nullptr;
		return reinterpret_cast<mstudiohitboxset_t*>(reinterpret_cast<uint8_t*>(this) + m_hitbox_set_index) + i;
	}

	mstudiobone_t* get_bone(int i) {
		if (i > m_num_bones) return nullptr;
		return reinterpret_cast<mstudiobone_t*>(reinterpret_cast<uint8_t*>(this) + m_bone_index) + i;
	}
};